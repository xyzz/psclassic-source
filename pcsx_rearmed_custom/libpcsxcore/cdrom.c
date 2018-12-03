/***************************************************************************
 *   Copyright (C) 2007 Ryan Schultz, PCSX-df Team, PCSX team              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.           *
 ***************************************************************************/

/*
* Handles all CD-ROM registers and functions.
*/

#include "cdrom.h"
#include "ppf.h"
#include "psxdma.h"
#include "arm_features.h"
#include "title.h"
#include "misc.h"
#include "../plugins/dfsound/externals.h"
#include "../plugins/dfsound/spu_config.h"
#include "../frontend/plugin_lib.h"

/* logging */
#if 0
#define CDR_LOG SysPrintf
#else
#define CDR_LOG(...)
#endif
#if 0
#define CDR_LOG_I SysPrintf
#else
#define CDR_LOG_I(...)
#endif
#if 0
#define CDR_LOG_IO SysPrintf
#else
#define CDR_LOG_IO(...)
#endif
//#define CDR_LOG_CMD_IRQ

cdrStruct cdr;
static unsigned char *pTransfer;

int is_disc_change = 0;
int is_nop_count = 0;
int nop_cnt = 0;
static int scenes=0;

/* CD-ROM magic numbers */
#define CdlSync        0
#define CdlNop         1
#define CdlSetloc      2
#define CdlPlay        3
#define CdlForward     4
#define CdlBackward    5
#define CdlReadN       6
#define CdlStandby     7
#define CdlStop        8
#define CdlPause       9
#define CdlInit        10
#define CdlMute        11
#define CdlDemute      12
#define CdlSetfilter   13
#define CdlSetmode     14
#define CdlGetmode     15
#define CdlGetlocL     16
#define CdlGetlocP     17
#define CdlReadT       18
#define CdlGetTN       19
#define CdlGetTD       20
#define CdlSeekL       21
#define CdlSeekP       22
#define CdlSetclock    23
#define CdlGetclock    24
#define CdlTest        25
#define CdlID          26
#define CdlReadS       27
#define CdlReset       28
#define CdlGetQ        29
#define CdlReadToc     30

char *CmdName[0x100]= {
    "CdlSync",     "CdlNop",       "CdlSetloc",  "CdlPlay",
    "CdlForward",  "CdlBackward",  "CdlReadN",   "CdlStandby",
    "CdlStop",     "CdlPause",     "CdlInit",    "CdlMute",
    "CdlDemute",   "CdlSetfilter", "CdlSetmode", "CdlGetmode",
    "CdlGetlocL",  "CdlGetlocP",   "CdlReadT",   "CdlGetTN",
    "CdlGetTD",    "CdlSeekL",     "CdlSeekP",   "CdlSetclock",
    "CdlGetclock", "CdlTest",      "CdlID",      "CdlReadS",
    "CdlReset",    NULL,           "CDlReadToc", NULL
};

unsigned char Test04[] = { 0 };
unsigned char Test05[] = { 0 };
unsigned char Test20[] = { 0x98, 0x06, 0x10, 0xC3 };
unsigned char Test22[] = { 0x66, 0x6F, 0x72, 0x20, 0x45, 0x75, 0x72, 0x6F };
unsigned char Test23[] = { 0x43, 0x58, 0x44, 0x32, 0x39 ,0x34, 0x30, 0x51 };

// cdr.Stat:
#define NoIntr		0
#define DataReady	1
#define Complete	2
#define Acknowledge	3
#define DataEnd		4
#define DiskError	5

/* Modes flags */
#define MODE_SPEED       (1<<7) // 0x80
#define MODE_STRSND      (1<<6) // 0x40 ADPCM on/off
#define MODE_SIZE_2340   (1<<5) // 0x20
#define MODE_SIZE_2328   (1<<4) // 0x10
#define MODE_SIZE_2048   (0<<4) // 0x00
#define MODE_SF          (1<<3) // 0x08 channel on/off
#define MODE_REPORT      (1<<2) // 0x04
#define MODE_AUTOPAUSE   (1<<1) // 0x02
#define MODE_CDDA        (1<<0) // 0x01

/* Status flags */
#define STATUS_PLAY      (1<<7) // 0x80
#define STATUS_SEEK      (1<<6) // 0x40
#define STATUS_READ      (1<<5) // 0x20
#define STATUS_SHELLOPEN (1<<4) // 0x10
#define STATUS_UNKNOWN3  (1<<3) // 0x08
#define STATUS_UNKNOWN2  (1<<2) // 0x04
#define STATUS_ROTATING  (1<<1) // 0x02
#define STATUS_ERROR     (1<<0) // 0x01

/* Errors */
#define ERROR_NOTREADY   (1<<7) // 0x80
#define ERROR_INVALIDCMD (1<<6) // 0x40
#define ERROR_INVALIDARG (1<<5) // 0x20

// 1x = 75 sectors per second
// PSXCLK = 1 sec in the ps
// so (PSXCLK / 75) = cdr read time (linuzappz)
#define cdReadTime (PSXCLK / 75)
// video sector head
#define CD_STR_HEAD (0x80010160)
#define CD_STR_HEAD_SIZE (0x20)

#define H_CDLeft 0x0db0
#define SET_VOLUME_L 0x1f801c00
#define SET_VOLUME_R 0x1f801c12
#define MAX_VOLUME 0x7fff
enum drive_state {
	DRIVESTATE_STANDBY = 0,
	DRIVESTATE_LID_OPEN,
	DRIVESTATE_RESCAN_CD,
	DRIVESTATE_PREPARE_CD,
	DRIVESTATE_STOPPED,
};

// for cdr.Seeked
enum seeked_state {
	SEEK_PENDING = 0,
	SEEK_DONE = 1,
};

static struct CdrStat stat;
static int isUseBuf = 0;
static int arc_sec_count = 0;
static int arc_sec_not_read = 0;

static int RunBiosLogoFarst = 0;

int Loading2Setloc = 0;

int xaSave_iLeftVolume;
int xaSave_iRightVolume;
unsigned char State_CdlPause;

#define ARC_BUFF_MAX (10)
static unsigned char arcSecBuf[ARC_BUFF_MAX][DATA_SIZE];

static unsigned int msf2sec(const u8 *msf) {
	return ((msf[0] * 60 + msf[1]) * 75) + msf[2];
}

// for that weird psemu API..
static unsigned int fsm2sec(const u8 *msf) {
	return ((msf[2] * 60 + msf[1]) * 75) + msf[0];
}

static void sec2msf(unsigned int s, u8 *msf) {
	msf[0] = s / 75 / 60;
	s = s - msf[0] * 75 * 60;
	msf[1] = s / 75;
	s = s - msf[1] * 75;
	msf[2] = s;
}

// cdrInterrupt
#define CDR_INT(eCycle) { \
	psxRegs.interrupt |= (1 << PSXINT_CDR); \
	psxRegs.intCycle[PSXINT_CDR].cycle = eCycle; \
	psxRegs.intCycle[PSXINT_CDR].sCycle = psxRegs.cycle; \
	new_dyna_set_event(PSXINT_CDR, eCycle); \
}

// cdrReadInterrupt
#define CDREAD_INT(eCycle) { \
	psxRegs.interrupt |= (1 << PSXINT_CDREAD); \
	psxRegs.intCycle[PSXINT_CDREAD].cycle = eCycle; \
	psxRegs.intCycle[PSXINT_CDREAD].sCycle = psxRegs.cycle; \
	new_dyna_set_event(PSXINT_CDREAD, eCycle); \
}

// cdrLidSeekInterrupt
#define CDRLID_INT(eCycle) { \
	psxRegs.interrupt |= (1 << PSXINT_CDRLID); \
	psxRegs.intCycle[PSXINT_CDRLID].cycle = eCycle; \
	psxRegs.intCycle[PSXINT_CDRLID].sCycle = psxRegs.cycle; \
	new_dyna_set_event(PSXINT_CDRLID, eCycle); \
}

// cdrPlayInterrupt
#define CDRMISC_INT(eCycle) { \
	psxRegs.interrupt |= (1 << PSXINT_CDRPLAY); \
	psxRegs.intCycle[PSXINT_CDRPLAY].cycle = eCycle; \
	psxRegs.intCycle[PSXINT_CDRPLAY].sCycle = psxRegs.cycle; \
	new_dyna_set_event(PSXINT_CDRPLAY, eCycle); \
}

#define StopReading() { \
	if (cdr.Reading) { \
		cdr.Reading = 0; \
		psxRegs.interrupt &= ~(1 << PSXINT_CDREAD); \
	} \
	cdr.StatP &= ~(STATUS_READ|STATUS_SEEK);\
}

#define StopCdda() { \
	if (cdr.Play) { \
		if (!Config.Cdda) CDR_stop(); \
		cdr.StatP &= ~STATUS_PLAY; \
		cdr.Play = FALSE; \
		cdr.FastForward = 0; \
		cdr.FastBackward = 0; \
		/*SPU_registerCallback( SPUirq );*/ \
	} \
}

#define SetResultSize(size) { \
	cdr.ResultP = 0; \
	cdr.ResultC = size; \
	cdr.ResultReady = 1; \
}

extern void change_HSync_Motionjpeg(int onfoff);
extern void change_frame_Motionjpeg(int onfoff);
extern void check_Motionjpeg(unsigned char arg1, unsigned char arg2, unsigned char arg3);
extern void set_scenes(int scenes);

int CheckDiscChange(unsigned short irq)
{
	// check exit conditions
	if ((is_disc_change || is_nop_count) && irq != CdlNop && irq != CdlSetmode && irq != CdlGetTN && irq != CdlSetloc && irq != CdlStop) {
		is_nop_count = 0;
		nop_cnt = 0;
		return 0;
	}

	// check initiation conditions
	if (!is_disc_change) {
		switch (disc_change_type) {
		case 1:
			if (irq == CdlStop) {
				is_nop_count = 0;
				nop_cnt = 0;
				return 1;
			}
			else if (irq == CdlPause) {
				is_nop_count = 1;
			}
			else if (irq == CdlNop && is_nop_count) {
				nop_cnt++;
				if (nop_cnt >= 20) {
					is_nop_count = 0;
					nop_cnt = 0;
					return 1;
				}
			}
			break;
		case 2:
			if (irq == CdlStop) {
				is_nop_count = 0;
				nop_cnt = 0;
				return 1;
			}
			else if (irq == CdlPause || irq == CdlReadN || irq == CdlReadS) {
				is_nop_count = 1;
			}
			else if (irq == CdlNop && is_nop_count) {
				nop_cnt++;
				if (nop_cnt >= 20) {
					is_nop_count = 0;
					nop_cnt = 0;
					return 1;
				}
			}
			break;
		case 3:
			if (irq == CdlStop) {
				is_nop_count = 0;
				nop_cnt = 0;
				return 1;
			}
			break;
		case 4:
			if (irq == CdlStop || irq == CdlPause) {
				is_nop_count = 0;
				nop_cnt = 0;
				return 1;
			}
			break;
		case 5:
			if (irq == CdlStop || irq == CdlReadN || irq == CdlReadS) {
				is_nop_count = 0;
				nop_cnt = 0;
				return 1;
			}
			else if (irq == CdlPause) {
				is_nop_count = 1;
			}
			else if (irq == CdlNop && is_nop_count) {
				nop_cnt++;
				if (nop_cnt >= 20) {
					is_nop_count = 0;
					nop_cnt = 0;
					return 1;
				}
			}
		}
		return 0;
	}
	return 1;
}

static void setIrq(void)
{
	if (cdr.Stat & cdr.Reg2)
		psxHu32ref(0x1070) |= SWAP32((u32)0x4);
}

// timing used in this function was taken from tests on real hardware
// (yes it's slow, but you probably don't want to modify it)
void cdrLidSeekInterrupt()
{
	switch (cdr.DriveState) {
	default:
	case DRIVESTATE_STANDBY:
		cdr.StatP &= ~STATUS_SEEK;

		if (CDR_getStatus(&stat) == -1)
			return;

		if (stat.Status & STATUS_SHELLOPEN)
		{
			StopCdda();
			cdr.DriveState = DRIVESTATE_LID_OPEN;
			CDRLID_INT(0x800);
		}
		break;

	case DRIVESTATE_LID_OPEN:
		if (CDR_getStatus(&stat) == -1)
			stat.Status &= ~STATUS_SHELLOPEN;

		// 02, 12, 10
		if (!(cdr.StatP & STATUS_SHELLOPEN)) {
			StopReading();
			cdr.StatP |= STATUS_SHELLOPEN;

			// could generate error irq here, but real hardware
			// only sometimes does that
			// (not done when lots of commands are sent?)

			CDRLID_INT(cdReadTime * 30);
			break;
		}
		else if (cdr.StatP & STATUS_ROTATING) {
			cdr.StatP &= ~STATUS_ROTATING;
		}
		else if (!(stat.Status & STATUS_SHELLOPEN)) {
			// closed now
			CheckCdrom();

			// cdr.StatP STATUS_SHELLOPEN is "sticky"
			// and is only cleared by CdlNop

			cdr.DriveState = DRIVESTATE_RESCAN_CD;
			CDRLID_INT(cdReadTime * 105);
			break;
		}

		// recheck for close
		CDRLID_INT(cdReadTime * 3);
		break;

	case DRIVESTATE_RESCAN_CD:
		cdr.StatP |= STATUS_ROTATING;
		cdr.DriveState = DRIVESTATE_PREPARE_CD;

		// this is very long on real hardware, over 6 seconds
		// make it a bit faster here...
		CDRLID_INT(cdReadTime * 150);
		break;

	case DRIVESTATE_PREPARE_CD:
		cdr.StatP |= STATUS_SEEK;

		cdr.DriveState = DRIVESTATE_STANDBY;
		CDRLID_INT(cdReadTime * 26);
		break;
	}
}

static void Find_CurTrack(const u8 *time)
{
	int current, sect;

	current = msf2sec(time);

	for (cdr.CurTrack = 1; cdr.CurTrack < cdr.ResultTN[1]; cdr.CurTrack++) {
		CDR_getTD(cdr.CurTrack + 1, cdr.ResultTD);
		sect = fsm2sec(cdr.ResultTD);
		if (sect - current >= 150)
			break;
	}
}

static void generate_subq(const u8 *time)
{
	unsigned char start[3], next[3];
	unsigned int this_s, start_s, next_s, pregap;
	int relative_s;

	CDR_getTD(cdr.CurTrack, start);
	if (cdr.CurTrack + 1 <= cdr.ResultTN[1]) {
		pregap = 150;
		CDR_getTD(cdr.CurTrack + 1, next);
	}
	else {
		// last track - cd size
		pregap = 0;
		next[0] = cdr.SetSectorEnd[2];
		next[1] = cdr.SetSectorEnd[1];
		next[2] = cdr.SetSectorEnd[0];
	}

	this_s = msf2sec(time);
	start_s = fsm2sec(start);
	next_s = fsm2sec(next);

	cdr.TrackChanged = FALSE;

	if (next_s - this_s < pregap) {
		cdr.TrackChanged = TRUE;
		cdr.CurTrack++;
		start_s = next_s;
	}

	cdr.subq.Index = 1;

	relative_s = this_s - start_s;
	if (relative_s < 0) {
		cdr.subq.Index = 0;
		relative_s = -relative_s;
	}
	sec2msf(relative_s, cdr.subq.Relative);

	cdr.subq.Track = itob(cdr.CurTrack);
	cdr.subq.Relative[0] = itob(cdr.subq.Relative[0]);
	cdr.subq.Relative[1] = itob(cdr.subq.Relative[1]);
	cdr.subq.Relative[2] = itob(cdr.subq.Relative[2]);
	cdr.subq.Absolute[0] = itob(time[0]);
	cdr.subq.Absolute[1] = itob(time[1]);
	cdr.subq.Absolute[2] = itob(time[2]);
}

static void ReadTrack(const u8 *time) {
	unsigned char tmp[3];
	struct SubQ *subq;
	u16 crc;

	tmp[0] = itob(time[0]);
	tmp[1] = itob(time[1]);
	tmp[2] = itob(time[2]);

	if (memcmp(cdr.Prev, tmp, 3) == 0)
		return;

	CDR_LOG("ReadTrack *** %02x:%02x:%02x\n", tmp[0], tmp[1], tmp[2]);

	if (isTitleName(METAL_GEAR_SOLID_DISC_1_JP) ||
		isTitleName(METAL_GEAR_SOLID_DISC_1_US) ||
		isTitleName(METAL_GEAR_SOLID_DISC_2_JP) ||
		isTitleName(METAL_GEAR_SOLID_DISC_2_US)) {
		check_Motionjpeg(tmp[0], tmp[1], tmp[2]);
		check_scenes(tmp[0], tmp[1], tmp[2]);
	}

	if (isTitleName(WILD_ARMS_US) ||
		isTitleName(WILD_ARMS_JP)) {
		check_scenesforSPU(tmp[0], tmp[1], tmp[2]);
	}

	cdr.RErr = CDR_readTrack(tmp);
	memcpy(cdr.Prev, tmp, 3);

	if (CheckSBI(time))
		return;

	subq = (struct SubQ *)CDR_getBufferSub();
	if (subq != NULL && cdr.CurTrack == 1) {
//		crc = calcCrc((u8 *)subq + 12, 10);
//		if (crc == (((u16)subq->CRC[0] << 8) | subq->CRC[1])) {
		if (subq->TrackNumber != 0) {
			cdr.subq.Track = subq->TrackNumber;
			cdr.subq.Index = subq->IndexNumber;
			memcpy(cdr.subq.Relative, subq->TrackRelativeAddress, 3);
			memcpy(cdr.subq.Absolute, subq->AbsoluteAddress, 3);
		}
		else {
			generate_subq(time);
			CDR_LOG_I("subq bad crc @%02x:%02x:%02x\n",
				tmp[0], tmp[1], tmp[2]);
		}
	}
	else {
		generate_subq(time);
	}

	CDR_LOG(" -> %02x,%02x %02x:%02x:%02x %02x:%02x:%02x\n",
		cdr.subq.Track, cdr.subq.Index,
		cdr.subq.Relative[0], cdr.subq.Relative[1], cdr.subq.Relative[2],
		cdr.subq.Absolute[0], cdr.subq.Absolute[1], cdr.subq.Absolute[2]);
}

static void AddIrqQueue(unsigned short irq, unsigned long ecycle) {
	if (cdr.Irq != 0) {
		if (irq == cdr.Irq || irq + 0x100 == cdr.Irq) {
			cdr.IrqRepeated = 1;
			CDR_INT(ecycle);
			return;
		}

		CDR_LOG_I("cdr: override cmd %02x -> %02x\n", cdr.Irq, irq);
	}

	cdr.Irq = irq;
	cdr.eCycle = ecycle;

	CDR_INT(ecycle);
}

static void cdrPlayInterrupt_Autopause()
{
	if ((cdr.Mode & MODE_AUTOPAUSE) && cdr.TrackChanged) {
		CDR_LOG( "CDDA STOP\n" );

		// Magic the Gathering
		// - looping territory cdda

		// ...?
		//cdr.ResultReady = 1;
		//cdr.Stat = DataReady;
		cdr.Stat = DataEnd;
		setIrq();

		StopCdda();
	}
	else if (cdr.Mode & MODE_REPORT) {

		cdr.Result[0] = cdr.StatP;
		cdr.Result[1] = cdr.subq.Track;
		cdr.Result[2] = cdr.subq.Index;

		if (cdr.subq.Absolute[2] & 0x10) {
			cdr.Result[3] = cdr.subq.Relative[0];
			cdr.Result[4] = cdr.subq.Relative[1] | 0x80;
			cdr.Result[5] = cdr.subq.Relative[2];
		}
		else {
			cdr.Result[3] = cdr.subq.Absolute[0];
			cdr.Result[4] = cdr.subq.Absolute[1];
			cdr.Result[5] = cdr.subq.Absolute[2];
		}

		cdr.Result[6] = 0;
		cdr.Result[7] = 0;

		// Rayman: Logo freeze (resultready + dataready)
		cdr.ResultReady = 1;
		cdr.Stat = DataReady;

		SetResultSize(8);
		setIrq();
	}
}

// also handles seek
void cdrPlayInterrupt()
{
	if (cdr.Seeked == SEEK_PENDING) {
		if (cdr.Stat) {
			CDR_LOG_I("cdrom: seek stat hack\n");
			CDRMISC_INT(0x1000);
			return;
		}
		SetResultSize(1);
		cdr.StatP |= STATUS_ROTATING;
		cdr.StatP &= ~STATUS_SEEK;
		cdr.Result[0] = cdr.StatP;
		cdr.Seeked = SEEK_DONE;
		if (cdr.Irq == 0) {
			cdr.Stat = Complete;
			setIrq();
		}

		if (cdr.SetlocPending) {
			memcpy(cdr.SetSectorPlay, cdr.SetSector, 4);
			cdr.SetlocPending = 0;
		}
		Find_CurTrack(cdr.SetSectorPlay);
		ReadTrack(cdr.SetSectorPlay);
		cdr.TrackChanged = FALSE;
	}

	if (!cdr.Play){
		if (isTitleName(TOSHINDEN_EU) ||
			isTitleName(TOSHINDEN_JP) ||
			isTitleName(TOSHINDEN_US)) {
			SPU_writeRegister(H_CDLeft, 0, psxRegs.cycle);
		}
		 return;
	}

	CDR_LOG( "CDDA - %d:%d:%d\n",
		cdr.SetSectorPlay[0], cdr.SetSectorPlay[1], cdr.SetSectorPlay[2] );

	if (memcmp(cdr.SetSectorPlay, cdr.SetSectorEnd, 3) == 0) {
		StopCdda();
		cdr.TrackChanged = TRUE;
	}

	if (!cdr.Irq && !cdr.Stat && (cdr.Mode & (MODE_AUTOPAUSE|MODE_REPORT)))
		cdrPlayInterrupt_Autopause();

	if (!cdr.Play) return;

	cdr.SetSectorPlay[2]++;
	if (cdr.SetSectorPlay[2] == 75) {
		cdr.SetSectorPlay[2] = 0;
		cdr.SetSectorPlay[1]++;
		if (cdr.SetSectorPlay[1] == 60) {
			cdr.SetSectorPlay[1] = 0;
			cdr.SetSectorPlay[0]++;
		}
	}

	CDRMISC_INT(cdReadTime);

	// update for CdlGetlocP/autopause
	generate_subq(cdr.SetSectorPlay);
}

void cdrInterrupt() {
	u16 Irq = cdr.Irq;
	int no_busy_error = 0;
	int start_rotating = 0;
	int error = 0;
	int delay;

	// Reschedule IRQ
	if (cdr.Stat) {
		CDR_LOG_I("cdrom: stat hack: %02x %x\n", cdr.Irq, cdr.Stat);
		CDR_INT(0x1000);
		return;
	}

	cdr.Ctrl &= ~0x80;

	// default response
	SetResultSize(1);
	cdr.Result[0] = cdr.StatP;
	cdr.Stat = Acknowledge;

	if (cdr.IrqRepeated) {
		cdr.IrqRepeated = 0;
		if (cdr.eCycle > psxRegs.cycle) {
			CDR_INT(cdr.eCycle);
			goto finish;
		}
	}

	cdr.Irq = 0;

	switch (Irq) {
		case CdlSync:
			// TOOD: sometimes/always return error?
			break;

		case CdlNop:
			if (cdr.DriveState != DRIVESTATE_LID_OPEN)
				cdr.StatP &= ~STATUS_SHELLOPEN;
			no_busy_error = 1;
			break;

		case CdlSetloc:
			break;

		do_CdlPlay:
		case CdlPlay:
			StopCdda();
			if (cdr.Seeked == SEEK_PENDING) {
				// XXX: wrong, should seek instead..
				cdr.Seeked = SEEK_DONE;
			}
			if (cdr.SetlocPending) {
				memcpy(cdr.SetSectorPlay, cdr.SetSector, 4);
				cdr.SetlocPending = 0;
			}

			// BIOS CD Player
			// - Pause player, hit Track 01/02/../xx (Setloc issued!!)

			if (cdr.ParamC == 0 || cdr.Param[0] == 0) {
				CDR_LOG("PLAY Resume @ %d:%d:%d\n",
					cdr.SetSectorPlay[0], cdr.SetSectorPlay[1], cdr.SetSectorPlay[2]);
			}
			else
			{
				int track = btoi( cdr.Param[0] );

				if (track <= cdr.ResultTN[1])
					cdr.CurTrack = track;

				CDR_LOG("PLAY track %d\n", cdr.CurTrack);

				if (CDR_getTD((u8)cdr.CurTrack, cdr.ResultTD) != -1) {
					cdr.SetSectorPlay[0] = cdr.ResultTD[2];
					cdr.SetSectorPlay[1] = cdr.ResultTD[1];
					cdr.SetSectorPlay[2] = cdr.ResultTD[0];
				}
			}

			/*
			Rayman: detect track changes
			- fixes logo freeze

			Twisted Metal 2: skip PREGAP + starting accurate SubQ
			- plays tracks without retry play

			Wild 9: skip PREGAP + starting accurate SubQ
			- plays tracks without retry play
			*/
			Find_CurTrack(cdr.SetSectorPlay);
			ReadTrack(cdr.SetSectorPlay);
			cdr.TrackChanged = FALSE;

			if (!Config.Cdda)
				CDR_play(cdr.SetSectorPlay);

			// Vib Ribbon: gameplay checks flag
			cdr.StatP &= ~STATUS_SEEK;
			cdr.Result[0] = cdr.StatP;

			cdr.StatP |= STATUS_PLAY;
			
			// BIOS player - set flag again
			cdr.Play = TRUE;

			CDRMISC_INT( cdReadTime );
			start_rotating = 1;
			break;

		case CdlForward:
			// TODO: error 80 if stopped
			cdr.Stat = Complete;

			// GameShark CD Player: Calls 2x + Play 2x
			if( cdr.FastForward == 0 ) cdr.FastForward = 2;
			else cdr.FastForward++;

			cdr.FastBackward = 0;
			break;

		case CdlBackward:
			cdr.Stat = Complete;

			// GameShark CD Player: Calls 2x + Play 2x
			if( cdr.FastBackward == 0 ) cdr.FastBackward = 2;
			else cdr.FastBackward++;

			cdr.FastForward = 0;
			break;

		case CdlStandby:
			if (cdr.DriveState != DRIVESTATE_STOPPED) {
				error = ERROR_INVALIDARG;
				goto set_error;
			}
			AddIrqQueue(CdlStandby + 0x100, cdReadTime * 125 / 2);
			start_rotating = 1;
			break;

		case CdlStandby + 0x100:
			cdr.Stat = Complete;
			break;

		case CdlStop:
			if (cdr.Play) {
				// grab time for current track
				CDR_getTD((u8)(cdr.CurTrack), cdr.ResultTD);

				cdr.SetSectorPlay[0] = cdr.ResultTD[2];
				cdr.SetSectorPlay[1] = cdr.ResultTD[1];
				cdr.SetSectorPlay[2] = cdr.ResultTD[0];
			}

			StopCdda();
			StopReading();

			delay = 0x800;
			if (cdr.DriveState == DRIVESTATE_STANDBY)
				delay = cdReadTime * 30 / 2;

			cdr.DriveState = DRIVESTATE_STOPPED;
			AddIrqQueue(CdlStop + 0x100, delay);
			break;

		case CdlStop + 0x100:
			cdr.StatP &= ~STATUS_ROTATING;
			cdr.Result[0] = cdr.StatP;
			cdr.Stat = Complete;
			break;

		case CdlPause:
			/*
			Gundam Battle Assault 2: much slower (*)
			- Fixes boot, gameplay

			Hokuto no Ken 2: slower
			- Fixes intro + subtitles

			InuYasha - Feudal Fairy Tale: slower
			- Fixes battles
			*/
			AddIrqQueue(CdlPause + 0x100, cdReadTime * 3);
			cdr.Ctrl |= 0x80;
			break;

		case CdlPause + 0x100:
			cdr.StatP &= ~STATUS_READ;
			cdr.Result[0] = cdr.StatP;
			cdr.Stat = Complete;
			break;

		case CdlInit:
			AddIrqQueue(CdlInit + 0x100, cdReadTime * 6);
			no_busy_error = 1;
			start_rotating = 1;
			break;

		case CdlInit + 0x100:
			cdr.Stat = Complete;
			break;

		case CdlMute:
			cdr.Muted = TRUE;
			break;

		case CdlDemute:
			cdr.Muted = FALSE;
			break;

		case CdlSetfilter:
			cdr.File = cdr.Param[0];
			cdr.Channel = cdr.Param[1];
			break;

		case CdlSetmode:
			no_busy_error = 1;
			break;

		case CdlGetmode:
			SetResultSize(6);
			cdr.Result[1] = cdr.Mode;
			cdr.Result[2] = cdr.File;
			cdr.Result[3] = cdr.Channel;
			cdr.Result[4] = 0;
			cdr.Result[5] = 0;
			no_busy_error = 1;
			break;

		case CdlGetlocL:
			SetResultSize(8);
			memcpy(cdr.Result, cdr.Transfer, 8);
			break;

		case CdlGetlocP:
			SetResultSize(8);
			memcpy(&cdr.Result, &cdr.subq, 8);

			if (!cdr.Play && !cdr.Reading)
				cdr.Result[1] = 0; // HACK?
			break;

		case CdlReadT: // SetSession?
			// really long
			AddIrqQueue(CdlReadT + 0x100, cdReadTime * 290 / 4);
			start_rotating = 1;
			break;

		case CdlReadT + 0x100:
			cdr.Stat = Complete;
			break;

		case CdlGetTN:
			SetResultSize(3);
			if (CDR_getTN(cdr.ResultTN) == -1) {
				cdr.Stat = DiskError;
				cdr.Result[0] |= STATUS_ERROR;
			} else {
				cdr.Stat = Acknowledge;
				cdr.Result[1] = itob(cdr.ResultTN[0]);
				cdr.Result[2] = itob(cdr.ResultTN[1]);
			}
			break;

		case CdlGetTD:
			cdr.Track = btoi(cdr.Param[0]);
			SetResultSize(4);
			if (CDR_getTD(cdr.Track, cdr.ResultTD) == -1) {
				cdr.Stat = DiskError;
				cdr.Result[0] |= STATUS_ERROR;
			} else {
				cdr.Stat = Acknowledge;
				cdr.Result[0] = cdr.StatP;
				cdr.Result[1] = itob(cdr.ResultTD[2]);
				cdr.Result[2] = itob(cdr.ResultTD[1]);
				cdr.Result[3] = itob(cdr.ResultTD[0]);
			}
			break;

		case CdlSeekL:
		case CdlSeekP:
			StopCdda();

			if (isTitleName(WILD_ARMS_US)) {
				if(cdr.SetSector[0] == 0x20 && cdr.SetSector[1] == 0x1c && cdr.SetSector[2] == 0x3d && scenes) {
					cdr.Seeked = SEEK_DONE;
					cdr.Stat = Complete;
					break;
				} else if(cdr.SetSector[0] == 0x26 && cdr.SetSector[1] == 0x32 && cdr.SetSector[2] == 0xb && scenes) {
					if (msf2sec(cdr.SetSector) <= msf2sec(cdr.SetSectorPlay)) {
						cdr.Seeked = SEEK_DONE;
						cdr.Stat = Complete;
						break;
					}
				}
			} else if (isTitleName(WILD_ARMS_JP)) {
				if(cdr.SetSector[0] == 0x20 && cdr.SetSector[1] == 0x1d && cdr.SetSector[2] == 0x6 && scenes) {
					cdr.Seeked = SEEK_DONE;
					cdr.Stat = Complete;
					break;
				} else if(cdr.SetSector[0] == 0x26 && cdr.SetSector[1] == 0x32 && cdr.SetSector[2] == 0x1f  && scenes) {
					if (msf2sec(cdr.SetSector) <= msf2sec(cdr.SetSectorPlay)) {
						cdr.Seeked = SEEK_DONE;
						cdr.Stat = Complete;
						break;
					}
				}
			}

			StopReading();
			cdr.StatP |= STATUS_SEEK;

			/*
			Crusaders of Might and Magic = 0.5x-4x
			- fix cutscene speech start

			Eggs of Steel = 2x-?
			- fix new game

			Medievil = ?-4x
			- fix cutscene speech

			Rockman X5 = 0.5-4x
			- fix capcom logo
			*/
			CDRMISC_INT(cdr.Seeked == SEEK_DONE ? 0x800 : cdReadTime * 4);
			cdr.Seeked = SEEK_PENDING;
			start_rotating = 1;
			break;

		case CdlTest:
			switch (cdr.Param[0]) {
				case 0x20: // System Controller ROM Version
					SetResultSize(4);
					memcpy(cdr.Result, Test20, 4);
					break;
				case 0x22:
					SetResultSize(8);
					memcpy(cdr.Result, Test22, 4);
					break;
				case 0x23: case 0x24:
					SetResultSize(8);
					memcpy(cdr.Result, Test23, 4);
					break;
			}
			no_busy_error = 1;
			break;

		case CdlID:
			AddIrqQueue(CdlID + 0x100, 20480);
			break;

		case CdlID + 0x100:
			SetResultSize(8);
			cdr.Result[0] = cdr.StatP;
			cdr.Result[1] = 0;
			cdr.Result[2] = 0;
			cdr.Result[3] = 0;

			// 0x10 - audio | 0x40 - disk missing | 0x80 - unlicensed
			if (CDR_getStatus(&stat) == -1 || stat.Type == 0 || stat.Type == 0xff) {
				cdr.Result[1] = 0xc0;
			}
			else {
				if (stat.Type == 2)
					cdr.Result[1] |= 0x10;
				if (CdromId[0] == '\0')
					cdr.Result[1] |= 0x80;
			}
			cdr.Result[0] |= (cdr.Result[1] >> 4) & 0x08;

			switch (CdromId[2]) {
			case 'P':
			case 'p':
				strncpy((char *)&cdr.Result[4], "SCEI", 4);
				break;
// To compliance the requirement, remove trademark notification
//			case 'E':
//			case 'e':
//				strncpy((char *)&cdr.Result[4], "SCEE", 4);
//				break;
//			case 'U':
//			case 'u':
//				strncpy((char *)&cdr.Result[4], "SCEA", 4);
//				break;
			default:
				strncpy((char *)&cdr.Result[4], "    ", 4);
				break;
			}
			cdr.Stat = Complete;
			break;

		case CdlReset:
			// yes, it really sets STATUS_SHELLOPEN
			cdr.StatP |= STATUS_SHELLOPEN;
			cdr.DriveState = DRIVESTATE_RESCAN_CD;
			CDRLID_INT(20480);
			no_busy_error = 1;
			start_rotating = 1;
			break;

		case CdlGetQ:
			// TODO?
			CDR_LOG_I("got CdlGetQ\n");
			break;

		case CdlReadToc:
			AddIrqQueue(CdlReadToc + 0x100, cdReadTime * 180 / 4);
			no_busy_error = 1;
			start_rotating = 1;
			break;

		case CdlReadToc + 0x100:
			cdr.Stat = Complete;
			no_busy_error = 1;
			break;

		case CdlReadN:
		case CdlReadS:
			if (cdr.SetlocPending) {
				memcpy(cdr.SetSectorPlay, cdr.SetSector, 4);
				cdr.SetlocPending = 0;
			}
			Find_CurTrack(cdr.SetSectorPlay);

			if ((cdr.Mode & MODE_CDDA) && cdr.CurTrack > 1)
				// Read* acts as play for cdda tracks in cdda mode
				goto do_CdlPlay;

			cdr.Reading = 1;
			cdr.FirstSector = 1;

			// Fighting Force 2 - update subq time immediately
			// - fixes new game
			ReadTrack(cdr.SetSectorPlay);


			// Crusaders of Might and Magic - update getlocl now
			// - fixes cutscene speech
			{
				u8 *buf = CDR_getBuffer();
				if (buf != NULL)
					memcpy(cdr.Transfer, buf, 8);
			}

			/*
			Duke Nukem: Land of the Babes - seek then delay read for one frame
			- fixes cutscenes
			C-12 - Final Resistance - doesn't like seek
			*/

			if (cdr.Seeked != SEEK_DONE) {
				cdr.StatP |= STATUS_SEEK;
				cdr.StatP &= ~STATUS_READ;

				// Crusaders of Might and Magic - use short time
				// - fix cutscene speech (startup)

				// ??? - use more accurate seek time later
				CDREAD_INT((cdr.Mode & 0x80) ? (cdReadTime / 2) : cdReadTime * 1);
			} else {
				cdr.StatP |= STATUS_READ;
				cdr.StatP &= ~STATUS_SEEK;

				CDREAD_INT((cdr.Mode & 0x80) ? (cdReadTime / 2) : cdReadTime * 1);
			}

			cdr.Result[0] = cdr.StatP;
			start_rotating = 1;
			break;

		default:
			CDR_LOG_I("Invalid command: %02x\n", Irq);
			error = ERROR_INVALIDCMD;
			// FALLTHROUGH

		set_error:
			SetResultSize(2);
			cdr.Result[0] = cdr.StatP | STATUS_ERROR;
			cdr.Result[1] = error;
			cdr.Stat = DiskError;
			break;
	}

	if (cdr.DriveState == DRIVESTATE_STOPPED && start_rotating) {
		cdr.DriveState = DRIVESTATE_STANDBY;
		cdr.StatP |= STATUS_ROTATING;
	}

	if (!no_busy_error) {
		switch (cdr.DriveState) {
		case DRIVESTATE_LID_OPEN:
		case DRIVESTATE_RESCAN_CD:
		case DRIVESTATE_PREPARE_CD:
			SetResultSize(2);
			cdr.Result[0] = cdr.StatP | STATUS_ERROR;
			cdr.Result[1] = ERROR_NOTREADY;
			cdr.Stat = DiskError;
			break;
		}
	}

finish:
	setIrq();
	cdr.ParamC = 0;

#ifdef CDR_LOG_CMD_IRQ
	{
		int i;
		SysPrintf("CDR IRQ %d cmd %02x stat %02x: ",
			!!(cdr.Stat & cdr.Reg2), Irq, cdr.Stat);
		for (i = 0; i < cdr.ResultC; i++)
			SysPrintf("%02x ", cdr.Result[i]);
		SysPrintf("\n");
	}
#endif
}

#ifdef HAVE_ARMV7
 #define ssat32_to_16(v) \
  asm("ssat %0,#16,%1" : "=r" (v) : "r" (v))
#else
 #define ssat32_to_16(v) do { \
  if (v < -32768) v = -32768; \
  else if (v > 32767) v = 32767; \
 } while (0)
#endif

void cdrAttenuate(s16 *buf, int samples, int stereo)
{
	int i, l, r;
	int ll = cdr.AttenuatorLeftToLeft;
	int lr = cdr.AttenuatorLeftToRight;
	int rl = cdr.AttenuatorRightToLeft;
	int rr = cdr.AttenuatorRightToRight;
	int shift;

	if (lr == 0 && rl == 0 && 0x78 <= ll && ll <= 0x88 && 0x78 <= rr && rr <= 0x88)
		return;

	if (!stereo && ll == 0x40 && lr == 0x40 && rl == 0x40 && rr == 0x40)
		return;

	if (isTitleName(ARMORED_CORE_JP) ||
			isTitleName(FINAL_FANTANSY_VII_DICS_1_EU) ||
			isTitleName(FINAL_FANTANSY_VII_DICS_1_JP) ||
			isTitleName(FINAL_FANTANSY_VII_DICS_1_US) ||
			isTitleName(FINAL_FANTANSY_VII_DICS_2_EU) ||
			isTitleName(FINAL_FANTANSY_VII_DICS_2_JP) ||
			isTitleName(FINAL_FANTANSY_VII_DICS_2_US) ||
			isTitleName(FINAL_FANTANSY_VII_DICS_3_EU) ||
			isTitleName(FINAL_FANTANSY_VII_DICS_3_JP) ||
			isTitleName(FINAL_FANTANSY_VII_DICS_3_US) ||
			isTitleName(FINAL_FANTANSY_VII_DICS_4_JP) ||
			isTitleName(G_DARIUS_JP) ||
			isTitleName(JUMPING_FLASH_EU) ||
			isTitleName(JUMPING_FLASH_JP) ||
			isTitleName(JUMPING_FLASH_US) ||
			isTitleName(PARASITE_EVE_DISC_1_JP) ||
			isTitleName(PARASITE_EVE_DISC_1_US) ||
			isTitleName(PARASITE_EVE_DISC_2_JP) ||
			isTitleName(PARASITE_EVE_DISC_2_US) ||
			isTitleName(TEKKEN3_EU) ||
			isTitleName(TEKKEN3_JP)) {
		shift = 8;
	} else {
		shift = 7;
	}

	if (stereo) {
		for (i = 0; i < samples; i++) {
			l = buf[i * 2];
			r = buf[i * 2 + 1];
			l = (l * ll + r * rl) >> shift;
			r = (r * rr + l * lr) >> shift;
			ssat32_to_16(l);
			ssat32_to_16(r);
			buf[i * 2] = l;
			buf[i * 2 + 1] = r;
		}
	}
	else {
		for (i = 0; i < samples; i++) {
			l = buf[i];
/* PLF-409 DEL Start */
//			l = l * (ll + rl) >> 7;
/* PLF-409 DEL End */
            if (isTitleName(MEDIEVIL_EU) ||
                isTitleName(MEDIEVIL_US)) {
                l = l * (ll + rl) >> shift;
            }
			//r = r * (rr + lr) >> 7;
			ssat32_to_16(l);
			//ssat32_to_16(r);
			buf[i] = l;
		}
	}
}

void cdrReadInterrupt() {
	u8 *buf;

	if (!cdr.Reading)
		return;

	if (cdr.Irq || cdr.Stat) {
		CDR_LOG_I("cdrom: read stat hack %02x %x\n", cdr.Irq, cdr.Stat);
		CDREAD_INT(0x1000);
		return;
	}

	cdr.OCUP = 1;
	SetResultSize(1);
	cdr.StatP |= STATUS_READ|STATUS_ROTATING;
	cdr.StatP &= ~STATUS_SEEK;
	cdr.Result[0] = cdr.StatP;
	cdr.Seeked = SEEK_DONE;

	if (isTitleName(DESTRUCTION_DERBY_EU) &&
			Loading2Setloc &&
			cdr.SetSectorPlay[0] == 0 &&
			cdr.SetSectorPlay[1] == 2 &&
			cdr.SetSectorPlay[2] == 23) {
		cdr.SetSectorPlay[2] = 22;
	}

	ReadTrack(cdr.SetSectorPlay);

	buf = CDR_getBuffer();
	if (buf == NULL)
		cdr.RErr = -1;

	if (cdr.RErr == -1) {
		CDR_LOG_I("cdrReadInterrupt() Log: err\n");
		memset(cdr.Transfer, 0, DATA_SIZE);
		cdr.Stat = DiskError;
		cdr.Result[0] |= STATUS_ERROR;
		CDREAD_INT((cdr.Mode & 0x80) ? (cdReadTime / 2) : cdReadTime);
		return;
	}

	const char searchLicenseString[] =
	  "          Licensed  by          Sony Computer Entertainment(Europe)\0\0\0\0";
	const char changeLicenseString[] =
	  "          Licensed  by          Sony Computer Entertainment(Eur  ope) \0";
	
	int searchLicenseStringLen = sizeof(searchLicenseString) - 1;
	int cnt = 0;
	int foundCnt = 0;
	
	if ((cdr.SetSectorPlay[0] == 0) &&
	    (cdr.SetSectorPlay[1] == 2) &&
	    (cdr.SetSectorPlay[2] == 4) &&
	    (cdr.SetSectorPlay[3] == 0)) {

		// License string area.
		while(cnt != DATA_SIZE) {
			if (*(buf + cnt) == searchLicenseString[foundCnt]) {
				if(++foundCnt == searchLicenseStringLen) {
					// found !!
					memcpy(buf + cnt - searchLicenseStringLen + 1,
					       changeLicenseString,
					       searchLicenseStringLen); 
					break;
				}
			} else {
				foundCnt = 0;
			}
			cnt ++;
		}
	}

	memcpy(cdr.Transfer, buf, DATA_SIZE);
	CheckPPFCache(cdr.Transfer, cdr.Prev[0], cdr.Prev[1], cdr.Prev[2]);

	if (isTitleName(PACAPACA_PASSION_JP)) {
		if (isUseBuf) {
			if (arc_sec_count >= ARC_BUFF_MAX)
				arc_sec_count = 0;
			memcpy(arcSecBuf[arc_sec_count++], buf, DATA_SIZE);
			CheckPPFCache(arcSecBuf[arc_sec_count-1], cdr.Prev[0], cdr.Prev[1], cdr.Prev[2]);
		}
	}

	CDR_LOG("cdrReadInterrupt() Log: cdr.Transfer %x:%x:%x\n", cdr.Transfer[0], cdr.Transfer[1], cdr.Transfer[2]);

	if ((!cdr.Muted) && (cdr.Mode & MODE_STRSND) && (!Config.Xa) && (cdr.FirstSector != -1)) { // CD-XA
		// Firemen 2: Multi-XA files - briefings, cutscenes
		if( cdr.FirstSector == 1 && (cdr.Mode & MODE_SF)==0 ) {
			cdr.File = cdr.Transfer[4 + 0];
			cdr.Channel = cdr.Transfer[4 + 1];
		}

		if((cdr.Transfer[4 + 2] & 0x4) &&
			 (cdr.Transfer[4 + 1] == cdr.Channel) &&
			 (cdr.Transfer[4 + 0] == cdr.File)) {
			int ret = xa_decode_sector(&cdr.Xa, cdr.Transfer+4, cdr.FirstSector);
			if (!ret) {
				cdrAttenuate(cdr.Xa.pcm, cdr.Xa.nsamples, cdr.Xa.stereo);
				SPU_playADPCMchannel(&cdr.Xa);
				cdr.FirstSector = 0;
			}
			else cdr.FirstSector = -1;
		}
	}

	if (isTitleName(PARAPPA_THE_RAPPER_US)
		&& cdr.SetSectorPlay[0] == 62
		&& cdr.SetSectorPlay[1] == 53
		&& cdr.SetSectorPlay[2] == 66) {
		cdrWrite1(0x08);
	}
	cdr.SetSectorPlay[2]++;
	if (cdr.SetSectorPlay[2] == 75) {
		cdr.SetSectorPlay[2] = 0;
		cdr.SetSectorPlay[1]++;
		if (cdr.SetSectorPlay[1] == 60) {
			cdr.SetSectorPlay[1] = 0;
			cdr.SetSectorPlay[0]++;
		}
	}

	cdr.Readed = 0;

	if (isTitleName(IQ_INTELLIGENT_QUBE_JP) &&
			cdr.SetSectorPlay[0] == 1 &&
			cdr.SetSectorPlay[1] == 55 &&
			(57 <= cdr.SetSectorPlay[2] && cdr.SetSectorPlay[2] <= 74)) {
		CDREAD_INT(cdReadTime / 2 * 0.5);
	} else if (isTitleName(IQ_INTELLIGENT_QUBE_US) &&
			cdr.SetSectorPlay[0] == 1 &&
			cdr.SetSectorPlay[1] == 20 &&
			(60 <= cdr.SetSectorPlay[2] && cdr.SetSectorPlay[2] <= 74)) {
		CDREAD_INT(cdReadTime / 2 * 0.5);
	} else if (isTitleName(WILD_ARMS_JP) &&
			cdr.SetSectorPlay[0] == 32 &&
			cdr.SetSectorPlay[1] == 29 &&
			(7 <= cdr.SetSectorPlay[2] && cdr.SetSectorPlay[2] <= 50)) {
		CDREAD_INT(cdReadTime / 2 * 0.9);
	} else if (isTitleName(WILD_ARMS_US) &&
			cdr.SetSectorPlay[0] == 32 &&
			(cdr.SetSectorPlay[1] == 28 &&
			(61 <= cdr.SetSectorPlay[2] && cdr.SetSectorPlay[2] <= 74)) ||
			(cdr.SetSectorPlay[1] == 29 &&
			(0 <= cdr.SetSectorPlay[2] && cdr.SetSectorPlay[2] <= 30))) {
		CDREAD_INT(cdReadTime / 2 * 0.9);
	} else {
		CDREAD_INT((cdr.Mode & MODE_SPEED) ? (cdReadTime / 2) : cdReadTime);
	}

	/*
	Croc 2: $40 - only FORM1 (*)
	Judge Dredd: $C8 - only FORM1 (*)
	Sim Theme Park - no adpcm at all (zero)
	*/

	if (!(cdr.Mode & MODE_STRSND) || !(cdr.Transfer[4+2] & 0x4)) {
		cdr.Stat = DataReady;
		setIrq();
	}

	// update for CdlGetlocP
	ReadTrack(cdr.SetSectorPlay);
}

/*
cdrRead0:
	bit 0,1 - mode
	bit 2 - unknown
	bit 3 - unknown
	bit 4 - unknown
	bit 5 - 1 result ready
	bit 6 - 1 dma ready
	bit 7 - 1 command being processed
*/

unsigned char cdrRead0(void) {
	if (cdr.ResultReady)
		cdr.Ctrl |= 0x20;
	else
		cdr.Ctrl &= ~0x20;

	if (cdr.OCUP)
		cdr.Ctrl |= 0x40;
//  else
//		cdr.Ctrl &= ~0x40;

	// What means the 0x10 and the 0x08 bits? I only saw it used by the bios
	cdr.Ctrl |= 0x18;

	CDR_LOG_IO("cdr r0: %02x\n", cdr.Ctrl);

	return psxHu8(0x1800) = cdr.Ctrl;
}

void cdrWrite0(unsigned char rt) {
	CDR_LOG_IO("cdr w0: %02x\n", rt);

	cdr.Ctrl = (rt & 3) | (cdr.Ctrl & ~3);
}

unsigned char cdrRead1(void) {
	if ((cdr.ResultP & 0xf) < cdr.ResultC)
		psxHu8(0x1801) = cdr.Result[cdr.ResultP & 0xf];
	else
		psxHu8(0x1801) = 0;
	cdr.ResultP++;
	if (cdr.ResultP == cdr.ResultC)
		cdr.ResultReady = 0;

	CDR_LOG_IO("cdr r1: %02x\n", psxHu8(0x1801));

	return psxHu8(0x1801);
}

void cdrWrite1(unsigned char rt) {
	u8 set_loc[3];
	int i;

	CDR_LOG_IO("cdr w1: %02x\n", rt);

	switch (cdr.Ctrl & 3) {
	case 0:
		break;
	case 3:
		cdr.AttenuatorRightToRightT = rt;
		return;
	default:
		return;
	}

	cdr.Cmd = rt;
	cdr.OCUP = 0;

#ifdef CDR_LOG_CMD_IRQ
	SysPrintf("CD1 write: %x (%s)", rt, CmdName[rt]);
	if (cdr.ParamC) {
		SysPrintf(" Param[%d] = {", cdr.ParamC);
		for (i = 0; i < cdr.ParamC; i++)
			SysPrintf(" %x,", cdr.Param[i]);
		SysPrintf("}\n");
	} else {
		SysPrintf("\n");
	}
#endif

	is_disc_change = CheckDiscChange(cdr.Cmd);

	cdr.ResultReady = 0;
	cdr.Ctrl |= 0x80;

	// cdr.Stat = NoIntr; 
	if (isTitleName(ARC_THE_LAD_JP)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x24 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 375);
			RunBiosLogoFarst = 1;
		} else if (cdr.Cmd == CdlPause &&
				cdr.SetSector[0] == 9 &&
				cdr.SetSector[1] == 41 &&
				cdr.SetSector[2] == 43) {
			SPU_enableRvbConfig(1);
			AddIrqQueue(cdr.Cmd, 0x800);
		} else if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x38 &&
				cdr.Param[1] == 0x24 &&
				cdr.Param[2] == 0x11) {
			SPU_enableRvbConfig(0);
			AddIrqQueue(cdr.Cmd, 0x800);
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(ARC_THE_LAD_2_JP)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x26 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 300);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(ARMORED_CORE_JP)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x22 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 450);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(COOL_BOARDERS_2_EU)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 450);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(CRASH_BANDICOOT_EU)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x24 && 
				cdr.Param[1] == 0x15 &&
				cdr.Param[2] == 0x4) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 60);
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(CRASH_BANDICOOT_US)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x24 &&
				cdr.Param[1] == 0x29 &&
				cdr.Param[2] == 0x1) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 60);
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(DESTRUCTION_DERBY_EU)) {
		if( cdr.Cmd == CdlSetloc) {
			if (cdr.Param[0] == 0x0 &&
					cdr.Param[1] == 0x2 &&
					cdr.Param[2] == 0x22) {
				Loading2Setloc = 1;
			} else {
				Loading2Setloc = 0;
			}
		}

		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x22 &&
				cdr.Param[2] == 0x1 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 300);
			RunBiosLogoFarst = 1;

		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(FINAL_FANTANSY_VII_DICS_1_US) ||
			isTitleName(FINAL_FANTANSY_VII_DICS_1_JP)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 450);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(G_DARIUS_JP)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 450);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(GRADIUS_GAIDEN_JP)) {
		if (cdr.Cmd == CdlPause) {
			State_CdlPause = 1;
			xaSave_iLeftVolume = 0xFFFF;
			xaSave_iRightVolume =0xFFFF;
		} else if (cdr.Cmd == CdlSetloc && State_CdlPause == 1) {
				if (xaSave_iLeftVolume != 0xFFFF) {
					spu.iLeftXAVol = xaSave_iLeftVolume;
					xaSave_iLeftVolume = 0xFFFF;
				}
				if (xaSave_iRightVolume != 0xFFFF) {
					spu.iRightXAVol = xaSave_iRightVolume;
					xaSave_iRightVolume = 0xFFFF;
				}
				State_CdlPause = 0;
		}
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x22 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 375);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(GRAND_THEFT_AUTO_EU)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x22 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 450);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}
		if (RunBiosLogoFarst == 1 &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25) {
			spu.dwNewChannel&=~(1<<4);
			spu.dwNewChannel&=~(1<<5);
			spu.s_chan[4].ADSRX.ReleaseRate = 0x5;
			spu.s_chan[5].ADSRX.ReleaseRate = 0x5;
			spu.s_chan[4].ADSRX.State = ADSR_RELEASE;
			spu.s_chan[5].ADSRX.State = ADSR_RELEASE;
			RunBiosLogoFarst = 0xFF;
		}

	} else if (isTitleName(G_DARIUS_JP)) {
		if((cdr.Cmd == CdlSetloc && cdr.Param[0] == 0x00 && cdr.Param[1] == 0x10 && cdr.Param[2] == 0x53) ||
			(cdr.Cmd == CdlSetloc && cdr.Param[0] == 0x27 && cdr.Param[1] == 0x19 && cdr.Param[2] == 0x64) ||
			(cdr.Cmd == CdlSetloc && cdr.Param[0] == 0x27 && cdr.Param[1] == 0x19 && cdr.Param[2] == 0x65)) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 60);
		} else if((cdr.Cmd == CdlSetloc && cdr.Param[0] == 0x00 && cdr.Param[1] == 0x19 && cdr.Param[2] == 0x42) ||
			(cdr.Cmd == CdlSetloc && cdr.Param[0] == 0x00 && cdr.Param[1] == 0x13 && cdr.Param[2] == 0x37) ||
			(cdr.Cmd == CdlSetloc && cdr.Param[0] == 0x00 && cdr.Param[1] == 0x14 && cdr.Param[2] == 0x38) ||
			(cdr.Cmd == CdlSetloc && cdr.Param[0] == 0x01 && cdr.Param[1] == 0x51 && cdr.Param[2] == 0x16)) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 58);
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(IQ_INTELLIGENT_QUBE_JP) ||
			isTitleName(IQ_INTELLIGENT_QUBE_US)) {
		if (cdr.Cmd == CdlReadS) {
			unsigned short volume = isTitleName(IQ_INTELLIGENT_QUBE_JP) ?
					IQ_JP_MAX_VOLUME : IQ_US_MAX_VOLUME;
			SPU_writeRegister(H_CDLeft, volume, psxRegs.cycle);
		}
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x22 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 450);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(JUMPING_FLASH_EU) ||
			isTitleName(JUMPING_FLASH_JP)) {
		if (isTitleName(JUMPING_FLASH_JP)) {
			if (cdr.Cmd == CdlSetloc &&
					cdr.Param[0] == 0x0 &&
					cdr.Param[1] == 0x2 &&
					cdr.Param[2] == 0x25 &&
					RunBiosLogoFarst == 0) {
				AddIrqQueue(cdr.Cmd, cdReadTime * 450);
				RunBiosLogoFarst = 1;
			} else if (cdr.Cmd == CdlSetloc &&
					cdr.Param[0] == 0x50 &&
					cdr.Param[1] == 0x30 &&
					cdr.Param[2] == 0x38) {
				AddIrqQueue(cdr.Cmd, cdReadTime * 7);
			} else if (cdr.Cmd == CdlSetloc &&
					cdr.Param[0] == 0x8 &&
					cdr.Param[1] == 0x20 &&
					cdr.Param[2] == 0x13) {
				AddIrqQueue(cdr.Cmd, cdReadTime * 7);
			} else if (cdr.Cmd == CdlSetloc &&
					cdr.Param[0] == 0x50 &&
					cdr.Param[1] == 0x44 &&
					cdr.Param[2] == 0x59) {
				AddIrqQueue(cdr.Cmd, cdReadTime * 7);
			} else if (cdr.Cmd == CdlSetloc &&
					cdr.Param[0] == 0x15 &&
					cdr.Param[1] == 0x7 &&
					cdr.Param[2] == 0x24) {
				AddIrqQueue(cdr.Cmd, cdReadTime * 7);
			} else if (cdr.Cmd == CdlSetloc &&
					cdr.Param[0] == 0x50 &&
					cdr.Param[1] == 0x59 &&
					cdr.Param[2] == 0x13) {
				AddIrqQueue(cdr.Cmd, cdReadTime * 7);
			} else if (cdr.Cmd == CdlSetloc &&
					cdr.Param[0] == 0x22 &&
					cdr.Param[1] == 0x17 &&
					cdr.Param[2] == 0x70) {
				AddIrqQueue(cdr.Cmd, cdReadTime * 7);
			} else if (cdr.Cmd == CdlSetloc &&
					cdr.Param[0] == 0x51 &&
					cdr.Param[1] == 0x13 &&
					cdr.Param[2] == 0x34) {
				AddIrqQueue(cdr.Cmd, cdReadTime * 7);
			} else if (cdr.Cmd == CdlSetloc &&
					cdr.Param[0] == 0x29 &&
					cdr.Param[1] == 0x42 &&
					cdr.Param[2] == 0x71) {
				AddIrqQueue(cdr.Cmd, cdReadTime * 7);
			} else if (cdr.Cmd == CdlSetloc &&
					cdr.Param[0] == 0x51 &&
					cdr.Param[1] == 0x27 &&
					cdr.Param[2] == 0x55) {
				AddIrqQueue(cdr.Cmd, cdReadTime * 7);
			} else if (cdr.Cmd == CdlSetloc &&
					cdr.Param[0] == 0x36 &&
					cdr.Param[1] == 0x4 &&
					cdr.Param[2] == 0x61) {
				AddIrqQueue(cdr.Cmd, cdReadTime * 7);
			} else if (cdr.Cmd == CdlSetloc &&
					cdr.Param[0] == 0x43 &&
					cdr.Param[1] == 0x11 &&
					cdr.Param[2] == 0x68) {
				AddIrqQueue(cdr.Cmd, cdReadTime * 7);
			} else {
				AddIrqQueue(cdr.Cmd, 0x800);
			}
		} else {
			if (cdr.Cmd == CdlSetloc &&
					cdr.Param[0] == 0x0 &&
					cdr.Param[1] == 0x2 &&
					cdr.Param[2] == 0x25 &&
					RunBiosLogoFarst == 0) {
					AddIrqQueue(cdr.Cmd, cdReadTime * 450);
					RunBiosLogoFarst = 1;
			} else {
				AddIrqQueue(cdr.Cmd, 0x800);
			}
		}

	} else if (isTitleName(KAGERO_JP)) {
		if (cdr.Cmd == CdlSetloc) {
			if (cdr.Param[0] == 0x24 && cdr.Param[1] == 0x16 && cdr.Param[2] == 0x64) {
				//movie
				AddIrqQueue(cdr.Cmd, cdReadTime * 15);
			} else if (cdr.Param[0] == 0x28 && cdr.Param[1] == 0x31 && cdr.Param[2] == 0x43) {
				//config
				AddIrqQueue(cdr.Cmd, cdReadTime * 25);
			} else if (cdr.Param[0] == 0x30 && cdr.Param[1] == 0x56 && cdr.Param[2] == 0x56) {
				//trapMake
				AddIrqQueue(cdr.Cmd, cdReadTime * 30);
			} else if (cdr.Param[0] == 0x35 && cdr.Param[1] == 0x42 && cdr.Param[2] == 0x73) {
				//logo
				AddIrqQueue(cdr.Cmd, cdReadTime);
			} else {
				AddIrqQueue(cdr.Cmd, 0x800);
			}
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(MEDIEVIL_EU)) {
		if (cdr.Cmd == CdlSetloc) {
			if ((cdr.Param[0] == 0x43 && cdr.Param[1] == 0x16 && cdr.Param[2] == 0x2) ||
					(cdr.Param[0] == 0x49 && cdr.Param[1] == 0x12 && cdr.Param[2] == 0x54)) {
				AddIrqQueue(cdr.Cmd, cdReadTime * 5);
			} else {
				AddIrqQueue(cdr.Cmd, 0x800);
			}
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(MEDIEVIL_US)) {
		if (cdr.Cmd == CdlSetloc) {
			if ((cdr.Param[0] == 0x38 && cdr.Param[1] == 0x7 && cdr.Param[2] == 0x26) ||
					(cdr.Param[0] == 0x44 && cdr.Param[1] == 0x4 && cdr.Param[2] == 0x3)) {
				AddIrqQueue(cdr.Cmd, cdReadTime * 5);
			} else {
				AddIrqQueue(cdr.Cmd, 0x800);
			}
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(METAL_GEAR_SOLID_DISC_1_EU) ||
			isTitleName(METAL_GEAR_SOLID_DISC_1_JP) ||
			isTitleName(METAL_GEAR_SOLID_DISC_1_US)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x22 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 400);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(MR_DRILLER_US) ||
			isTitleName(MR_DRILLER_JP)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 150);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

        } else if (isTitleName(ODDWORLD_ABES_ODDYSEE_EU)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 400);
			RunBiosLogoFarst = 1;
		} else if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x09 &&
				cdr.Param[1] == 0x57 &&
				cdr.Param[2] == 0x61) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 60);
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

        } else if (isTitleName(ODDWORLD_ABES_ODDYSEE_US)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 400);
			RunBiosLogoFarst = 1;
		} else if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x09 &&
				cdr.Param[1] == 0x58 &&
				cdr.Param[2] == 0x64) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 60);
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(PARASITE_EVE_DISC_1_US) ||
			isTitleName(PARASITE_EVE_DISC_1_JP)) {
		if (isTitleName(PARASITE_EVE_DISC_1_JP)){
			if (cdr.Cmd == CdlSetloc) {
				if( (cdr.Param[0] == 0x2 && cdr.Param[1] == 0x11 && cdr.Param[2] == 0x63) ||
						(cdr.Param[0] == 0x0 && cdr.Param[1] == 0x27 && cdr.Param[2] == 0x64) ) {
					spu_config.iTempo = 1;
				} else if( (cdr.Param[0] == 0x0 && cdr.Param[1] == 0x17 && cdr.Param[2] == 0x44) ||
						(cdr.Param[0] == 0x11 && cdr.Param[1] == 0x9  && cdr.Param[2] == 0x37)) {
					spu_config.iTempo = 0;
				} else if (cdr.Param[0] == 0x40 && cdr.Param[1] == 0x38 && cdr.Param[2] == 0x42) {
					SPU_writeRegister(SET_VOLUME_L, PARASITE_EVE_JP_DISABLE_VOLUME, psxRegs.cycle);
					SPU_writeRegister(SET_VOLUME_R, PARASITE_EVE_JP_DISABLE_VOLUME, psxRegs.cycle);
				} else if (cdr.Param[0] == 0x11 && cdr.Param[1] == 0x8 && cdr.Param[2] == 0x6) {
					SPU_enableRvbConfig(1);
				} else if (cdr.Param[0] == 0x11 && cdr.Param[1] == 0x11 && cdr.Param[2] == 0x68) {
					SPU_enableRvbConfig(0);
				}
			}
		}

		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x15 &&
				cdr.Param[2] == 0x38) {
			spu_config.iTempo = 1;
		}

		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 150);
			RunBiosLogoFarst = 1;
		} else if (isTitleName(PARASITE_EVE_DISC_1_JP) &&
				cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x2 &&
				cdr.Param[1] == 0x11 &&
				cdr.Param[2] == 0x63) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 30);
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(PARASITE_EVE_DISC_2_US) ||
			isTitleName(PARASITE_EVE_DISC_2_JP)) {
		if (cdr.Cmd == CdlSetloc) {
			if( cdr.Param[0] == 0x11 &&
					cdr.Param[1] == 0x35 &&
					cdr.Param[2] == 0x10) {
				spu_config.iTempo = 0;
			} else if (cdr.Param[0] == 0x11 &&
					cdr.Param[1] == 0x35 &&
					cdr.Param[2] == 0x18) {
				spu_config.iTempo = 0;
			}
		}
		AddIrqQueue(cdr.Cmd, 0x800);

	} else if (isTitleName(PERSONA_JP) ||
			isTitleName(PERSONA_US)) {
		if (isTitleName(PERSONA_JP) && cdr.Cmd == CdlSetloc) {
			if (cdr.Param[0] == 0x0 &&
					cdr.Param[1] == 0x14 &&
					cdr.Param[2] == 0x61) {
				// "Adjust tempo" ON
				spu_config.iTempo = 1;
			}
		} else if (isTitleName(PERSONA_US) && cdr.Cmd == CdlSetloc) {
			if (cdr.Param[0] == 0x0 &&
					cdr.Param[1] == 0x17 &&
					cdr.Param[2] == 0x15) {
				// "Adjust tempo" ON
				spu_config.iTempo = 1;
			}
		}
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x22 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 400);
			RunBiosLogoFarst = 1;
			// "Adjust tempo" OFF
			spu_config.iTempo = 0;
		} else if (isTitleName(PERSONA_JP) && cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x18 &&
				cdr.Param[1] == 0x57 &&
				cdr.Param[2] == 0x6) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 45);
		} else if (isTitleName(PERSONA_US) && cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x18 &&
				cdr.Param[1] == 0x57 &&
				cdr.Param[2] == 0x33) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 45);
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(RAYMAN_US)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 400);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(RESIDENT_EVIL_EU) ||
			isTitleName(RESIDENT_EVIL_JP) ||
			isTitleName(RESIDENT_EVIL_US)) {

		if (isTitleName(RESIDENT_EVIL_JP)) {
			if (cdr.Cmd == CdlSetloc &&
					cdr.Param[0] == 0x35 &&
					cdr.Param[1] == 0x35 &&
					cdr.Param[2] == 0x42) {
				// NewGame selected "Adjust tempo" ON
				spu_config.iTempo = 1;
			} else if (cdr.Cmd == CdlSetloc &&
					cdr.Param[0] == 0x35 &&
					cdr.Param[1] == 0x35 &&
					cdr.Param[2] == 0x40) {
				// CharacterSelect selected "Adjust tempo" OFF
				spu_config.iTempo = 0;
			}
		}

		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x22 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 300);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}
		if (RunBiosLogoFarst == 1 &&
				((cdr.Param[0] == 0x65 && cdr.Param[1] == 0x14 && cdr.Param[2] == 0x4) ||  //US
				 (cdr.Param[0] == 0x63 && cdr.Param[1] == 0x53 && cdr.Param[2] == 0x47) || //JP
				 (cdr.Param[0] == 0x63 && cdr.Param[1] == 0x17 && cdr.Param[2] == 0x4))) { //EU
			spu.dwNewChannel&=~(1<<4);
			spu.dwNewChannel&=~(1<<5);
			spu.s_chan[4].ADSRX.State = ADSR_RELEASE;
			spu.s_chan[5].ADSRX.State = ADSR_RELEASE;
			RunBiosLogoFarst = 0xFF;
		}

	} else if (isTitleName(RIDGE_RACER_TYPE_4_EU) ||
			isTitleName(RIDGE_RACER_TYPE_4_JP) ||
			isTitleName(RIDGE_RACER_TYPE_4_US)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 400);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(SAGAFRONTIER_JP)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 300);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(SUPER_PUZZLE_FIGHTER_2_TURBO_US)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 450);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(SUPER_PUZZLE_FIGHTER_2_X_JP)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 375);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(SYPHON_FILTER_US)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 150);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(TEKKEN3_EU) ||
			isTitleName(TEKKEN3_JP)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 150);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(TOM_CLANCYS_RAINBOW_SIX_EU)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x22 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 450);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(TOSHINDEN_EU) ||
			isTitleName(TOSHINDEN_JP) ||
			isTitleName(TOSHINDEN_US)) {
		if (cdr.Cmd == CdlPlay) {
			unsigned short volume = isTitleName(TOSHINDEN_JP) ?
					TOSHINDEN_JP_DEFAULT_VOLUME : TOSHINDEN_DEFAULT_VOLUME;
			SPU_writeRegister(H_CDLeft, volume | 0x8000, psxRegs.cycle);
		} else if (cdr.Cmd == CdlPause) {
			SPU_writeRegister(H_CDLeft, 0x8000, psxRegs.cycle);
		}
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 450);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(TWISTED_METAL_US)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 450);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(WILD_ARMS_US) ||
			isTitleName(WILD_ARMS_JP)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 450);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}

	} else if (isTitleName(XI_EU) ||
			isTitleName(XI_JP)) {
		if (cdr.Cmd == CdlSetloc &&
				cdr.Param[0] == 0x0 &&
				cdr.Param[1] == 0x2 &&
				cdr.Param[2] == 0x25 &&
				RunBiosLogoFarst == 0) {
			AddIrqQueue(cdr.Cmd, cdReadTime * 450);
			RunBiosLogoFarst = 1;
		} else {
			AddIrqQueue(cdr.Cmd, 0x800);
		}
	} else {
		AddIrqQueue(cdr.Cmd, 0x800);
	}

	if (RunBiosLogoFarst) pl_rearmed_cbs.gpu_peops.isBiosLogoEnd = 1;

	switch (cdr.Cmd) {
	case CdlSetloc:
		for (i = 0; i < 3; i++)
			set_loc[i] = btoi(cdr.Param[i]);

		i = msf2sec(cdr.SetSectorPlay);
		i = abs(i - msf2sec(set_loc));
		if (i > 16)
			cdr.Seeked = SEEK_PENDING;

		memcpy(cdr.SetSector, set_loc, 3);
		cdr.SetSector[3] = 0;
		cdr.SetlocPending = 1;
		if (isTitleName(PACAPACA_PASSION_JP)) {
			unsigned char sector_s[4] = {0, 15, 24, 0};
			unsigned char sector_e[4] = {4, 0,  33, 0};
			int arc_file_s = msf2sec(sector_s);
			int arc_file_e = msf2sec(sector_e);
			int set_sector = msf2sec(cdr.SetSector);
			if (arc_file_s <= set_sector && set_sector <= arc_file_e) {
				isUseBuf = 1;
				arc_sec_count = 0;
				arc_sec_not_read = 0;
				memset(arcSecBuf, 0, DATA_SIZE * ARC_BUFF_MAX);
			}
			else {
				isUseBuf = 0;
			}
		}
		break;

	case CdlReadN:
	case CdlReadS:
	case CdlPause:
		StopCdda();
		StopReading();
		break;

	case CdlReset:
	case CdlInit:
		cdr.Seeked = SEEK_DONE;
		StopCdda();
		StopReading();
		break;

    	case CdlSetmode:
		CDR_LOG("cdrWrite1() Log: Setmode %x\n", cdr.Param[0]);

        	cdr.Mode = cdr.Param[0];

		// Squaresoft on PlayStation 1998 Collector's CD Vol. 1
		// - fixes choppy movie sound
		if( cdr.Play && (cdr.Mode & MODE_CDDA) == 0 )
			StopCdda();
        	break;
	}
}

unsigned char cdrRead2(void) {
	unsigned char ret;

	if (cdr.Readed == 0) {
		ret = 0;
	} else {
		ret = *pTransfer++;
	}

	CDR_LOG_IO("cdr r2: %02x\n", ret);
	return ret;
}

void cdrWrite2(unsigned char rt) {
	CDR_LOG_IO("cdr w2: %02x\n", rt);

	switch (cdr.Ctrl & 3) {
	case 0:
		if (cdr.ParamC < 8) // FIXME: size and wrapping
			cdr.Param[cdr.ParamC++] = rt;
		return;
	case 1:
		cdr.Reg2 = rt;
		setIrq();
		return;
	case 2:
		cdr.AttenuatorLeftToLeftT = rt;
		return;
	case 3:
		cdr.AttenuatorRightToLeftT = rt;
		return;
	}
}

unsigned char cdrRead3(void) {
	if (cdr.Ctrl & 0x1)
		psxHu8(0x1803) = cdr.Stat | 0xE0;
	else
		psxHu8(0x1803) = cdr.Reg2 | 0xE0;

	CDR_LOG_IO("cdr r3: %02x\n", psxHu8(0x1803));
	return psxHu8(0x1803);
}

void cdrWrite3(unsigned char rt) {
	CDR_LOG_IO("cdr w3: %02x\n", rt);

	switch (cdr.Ctrl & 3) {
	case 0:
		break; // transfer
	case 1:
		cdr.Stat &= ~rt;

		if (rt & 0x40)
			cdr.ParamC = 0;
		return;
	case 2:
		cdr.AttenuatorLeftToRightT = rt;
		return;
	case 3:
		if (rt & 0x20) {
			memcpy(&cdr.AttenuatorLeftToLeft, &cdr.AttenuatorLeftToLeftT, 4);
			if (isTitleName(RESIDENT_EVIL_EU) ||
					isTitleName(RESIDENT_EVIL_JP) ||
					isTitleName(RESIDENT_EVIL_US)) {
				unsigned short volume;
				volume = fmin((cdr.AttenuatorLeftToLeft + cdr.AttenuatorRightToLeft) << 8, MAX_VOLUME); 
				SPU_writeRegister(H_CDLeft, volume, psxRegs.cycle);
			}
			CDR_LOG_I("CD-XA Volume: %02x %02x | %02x %02x\n",
				cdr.AttenuatorLeftToLeft, cdr.AttenuatorLeftToRight,
				cdr.AttenuatorRightToLeft, cdr.AttenuatorRightToRight);
		}
		return;
	}

	if ((rt & 0x80) && cdr.Readed == 0) {
		cdr.Readed = 1;
		pTransfer = cdr.Transfer;

		switch (cdr.Mode & 0x30) {
			case MODE_SIZE_2328:
			case 0x00:
				pTransfer += 12;
				break;

			case MODE_SIZE_2340:
				pTransfer += 0;
				break;

			default:
				break;
		}
	}
}

void psxDma3(u32 madr, u32 bcr, u32 chcr) {
	u32 cdsize;
	int size;
	u8 *ptr;

	CDR_LOG("psxDma3() Log: *** DMA 3 *** %x addr = %x size = %x\n", chcr, madr, bcr);

	switch (chcr) {
		case 0x11000000:
		case 0x11400100:
			if (cdr.Readed == 0) {
				CDR_LOG("psxDma3() Log: *** DMA 3 *** NOT READY\n");
				break;
			}

			cdsize = (bcr & 0xffff) * 4;

			// Ape Escape: bcr = 0001 / 0000
			// - fix boot
			if( cdsize == 0 )
			{
				switch (cdr.Mode & (MODE_SIZE_2340|MODE_SIZE_2328)) {
					case MODE_SIZE_2340: cdsize = 2340; break;
					case MODE_SIZE_2328: cdsize = 2328; break;
					default:
					case MODE_SIZE_2048: cdsize = 2048; break;
				}
			}


			ptr = (u8 *)PSXM(madr);
			if (ptr == NULL) {
				CDR_LOG("psxDma3() Log: *** DMA 3 *** NULL Pointer!\n");
				break;
			}

			/*
			GS CDX: Enhancement CD crash
			- Setloc 0:0:0
			- CdlPlay
			- Spams DMA3 and gets buffer overrun
			*/
			size = CD_FRAMESIZE_RAW - (pTransfer - cdr.Transfer);
			if (size > cdsize)
				size = cdsize;
			if (size > 0)
			{
				if (isUseBuf && isTitleName(PACAPACA_PASSION_JP)) {
					if (arc_sec_not_read >= ARC_BUFF_MAX) arc_sec_not_read = 0; // reset ring buffer
					memcpy(ptr, arcSecBuf[arc_sec_not_read++] + (pTransfer - cdr.Transfer), size);
				}
				else {
					memcpy(ptr, pTransfer, size);
				}
			}

			psxCpu->Clear(madr, cdsize / 4);
			pTransfer += cdsize;

			if( chcr == 0x11400100 ) {
				HW_DMA3_MADR = SWAPu32(madr + cdsize);
				CDRDMA_INT( (cdsize/4) / 4 );
			}
			else if( chcr == 0x11000000 ) {
				// CDRDMA_INT( (cdsize/4) * 1 );
				// halted
				psxRegs.cycle += (cdsize/4) * 24/2;
				CDRDMA_INT(16);
				int left_cycle = psxRegs.intCycle[PSXINT_CDREAD].sCycle
								+ psxRegs.intCycle[PSXINT_CDREAD].cycle
								- psxRegs.cycle;
				u32 str_headr = *((u32*)ptr);
				if(left_cycle <= 0x1000
					&& size == CD_STR_HEAD_SIZE
					&& ((str_headr&CD_STR_HEAD) == CD_STR_HEAD)) {
					CDREAD_INT(0x1000);
					CDR_LOG("psxDma3() Log: CDREAD_INT(0x1000)\n");
				}
			}
			return;

		default:
			CDR_LOG("psxDma3() Log: Unknown cddma %x\n", chcr);
			break;
	}

	HW_DMA3_CHCR &= SWAP32(~0x01000000);
	DMA_INTERRUPT(3);
}

void cdrDmaInterrupt()
{
	if (HW_DMA3_CHCR & SWAP32(0x01000000))
	{
		HW_DMA3_CHCR &= SWAP32(~0x01000000);
		DMA_INTERRUPT(3);
	}
}

static void getCdInfo(void)
{
	u8 tmp;

	CDR_getTN(cdr.ResultTN);
	CDR_getTD(0, cdr.SetSectorEnd);
	tmp = cdr.SetSectorEnd[0];
	cdr.SetSectorEnd[0] = cdr.SetSectorEnd[2];
	cdr.SetSectorEnd[2] = tmp;
}

void cdrReset() {
	memset(&cdr, 0, sizeof(cdr));
	cdr.CurTrack = 1;
	cdr.File = 1;
	cdr.Channel = 1;
	cdr.Reg2 = 0x1f;
	cdr.Stat = NoIntr;
	cdr.DriveState = DRIVESTATE_STANDBY;
	cdr.StatP = STATUS_ROTATING;
	pTransfer = cdr.Transfer;

	// BIOS player - default values
	cdr.AttenuatorLeftToLeft = 0x80;
	cdr.AttenuatorLeftToRight = 0x00;
	cdr.AttenuatorRightToLeft = 0x00;
	cdr.AttenuatorRightToRight = 0x80;

	getCdInfo();
}

int cdrFreeze(void *f, int Mode) {
	u32 tmp;
	u8 tmpp[3];

	if(Mode == 2) {
		int iRetSize = sizeof(cdr) \
		  + sizeof(tmp);

		if(f) {
			cdr.freeze_ver = 0x63647202;
			memcpy(f, &cdr, sizeof(cdr));
			f = (void *)((char *)f + sizeof(cdr));

			cdr.ParamP = cdr.ParamC;
			tmp = pTransfer - cdr.Transfer;
			memcpy(f, &tmp, sizeof(tmp));
			f = (void *)((char *)f + sizeof(tmp));
		}
		return iRetSize;
	}
	if (Mode == 0 && !Config.Cdda)
		CDR_stop();
	
	cdr.freeze_ver = 0x63647202;
	gzfreeze(&cdr, sizeof(cdr));
	
	if (Mode == 1) {
		cdr.ParamP = cdr.ParamC;
		tmp = pTransfer - cdr.Transfer;
	}

	gzfreeze(&tmp, sizeof(tmp));

	if (Mode == 0) {
		getCdInfo();

		pTransfer = cdr.Transfer + tmp;

		// read right sub data
		memcpy(tmpp, cdr.Prev, 3);
		cdr.Prev[0]++;
		ReadTrack(tmpp);

		if (cdr.Play) {
			if (cdr.freeze_ver < 0x63647202)
				memcpy(cdr.SetSectorPlay, cdr.SetSector, 3);

			Find_CurTrack(cdr.SetSectorPlay);
			if (!Config.Cdda)
				CDR_play(cdr.SetSectorPlay);
		}

		if ((cdr.freeze_ver & 0xffffff00) != 0x63647200) {
			// old versions did not latch Reg2, have to fixup..
			if (cdr.Reg2 == 0) {
				SysPrintf("cdrom: fixing up old savestate\n");
				cdr.Reg2 = 7;
			}
			// also did not save Attenuator..
			if ((cdr.AttenuatorLeftToLeft | cdr.AttenuatorLeftToRight
			     | cdr.AttenuatorRightToLeft | cdr.AttenuatorRightToRight) == 0)
			{
				cdr.AttenuatorLeftToLeft = cdr.AttenuatorRightToRight = 0x80;
			}
		}
	}

	return 0;
}

void LidInterrupt() {
	getCdInfo();
	StopCdda();
	cdrLidSeekInterrupt();
}

int mgs_disk1_jp[][2] = {
		{0x605657,0x624116},
		{0x600452,0x605644},
		{0x624124,0x640462},
		{0x585550,0x600441}
};
int mgs_disk2_jp[][2] = {
		{0x510434,0x520847},
		{0x520868,0x543706},
		{0x550948,0x672735},
		{0x543723,0x550923}
};
int mgs_disk1_us[][2] = {
		{0x603166,0x621624},
		{0x593961,0x603152},
		{0x621632,0x633969},
		{0x583059,0x593948}
};
int mgs_disk2_us[][2] = {
		{0x504407,0x514820},
		{0x514840,0x541652},
		{0x544911,0x670059},
		{0x541661,0x544862}
};

void check_Motionjpeg(unsigned char arg1, unsigned char arg2, unsigned char arg3){

	int i,hit=0;
	int track=arg1<<16|arg2<<8|arg3;

	if (isTitleName(METAL_GEAR_SOLID_DISC_1_JP)){
		for(i=0; i < sizeof(mgs_disk1_jp)/sizeof(mgs_disk1_jp[0]); i++){
			if((track >= mgs_disk1_jp[i][0]) && (track <= mgs_disk1_jp[i][1])){
				hit=1;
				break;
			}
		}
	}
	else if (isTitleName(METAL_GEAR_SOLID_DISC_2_JP)){
		for(i=0; i < sizeof(mgs_disk2_jp)/sizeof(mgs_disk2_jp[0]); i++){
			if((track >= mgs_disk2_jp[i][0]) && (track <= mgs_disk2_jp[i][1])){
				hit=1;
				break;
			}
		}
	}
	else if (isTitleName(METAL_GEAR_SOLID_DISC_1_US)){
		for(i=0; i < sizeof(mgs_disk1_us)/sizeof(mgs_disk1_us[0]); i++){
			if((track >= mgs_disk1_us[i][0]) && (track <= mgs_disk1_us[i][1])){
				hit=1;
				break;
			}
		}
	}
	else if (isTitleName(METAL_GEAR_SOLID_DISC_2_US)){
		for(i=0; i < sizeof(mgs_disk2_us)/sizeof(mgs_disk2_us[0]); i++){
			if((track >= mgs_disk2_us[i][0]) && (track <= mgs_disk2_us[i][1])){
				hit=1;
				break;
			}
		}
	}

	if(hit){
		change_HSync_Motionjpeg(1);
		change_frame_Motionjpeg(1);
	}
	else{
		change_HSync_Motionjpeg(0);
		change_frame_Motionjpeg(0);
	}
}

int mgs_disk1_scenes_jp[][3] = {
		{0x284037,0x284334,MSG_SCENE1},
		{0x141408,0x141936,MSG_SCENE2},
		{0x145317,0x145821,MSG_SCENE3},
		{0x173745,0x174574,MSG_SCENE4},
		{0x250774,0x251000,MSG_SCENE5},
		{0x255266,0x255853,MSG_SCENE6},
		{0x114172,0x114558,MSG_SCENE7},
		{0x072815,0x074943,MSG_SCENE8}
};
int mgs_disk1_scenes_us[][3] = {
		{0x284444,0x284770,MSG_SCENE1},
		{0x141817,0x142357,MSG_SCENE2},
		{0x145743,0x150240,MSG_SCENE3},
		{0x174225,0x175022,MSG_SCENE4},
		{0x251241,0x251435,MSG_SCENE5},
		{0x255753,0x260318,MSG_SCENE6},
		{0x114623,0x114969,MSG_SCENE7},
		{0x073234,0x075411,MSG_SCENE8}
};

void check_scenes(unsigned char arg1, unsigned char arg2, unsigned char arg3) {
	int i,hit = 0;
	int track = arg1 << 16 | arg2 << 8 | arg3;

	if (isTitleName(METAL_GEAR_SOLID_DISC_1_JP)) {
		for (i = 0; i < sizeof(mgs_disk1_scenes_jp) / sizeof(mgs_disk1_scenes_jp[0]); i++) {
			if ((track >= mgs_disk1_scenes_jp[i][0]) && (track <= mgs_disk1_scenes_jp[i][1])) {
				hit = mgs_disk1_scenes_jp[i][2];
				break;
			}
		}
	}
	else if (isTitleName(METAL_GEAR_SOLID_DISC_1_US)) {
		for (i = 0; i < sizeof(mgs_disk1_scenes_us) / sizeof(mgs_disk1_scenes_us[0]); i++) {
			if ((track >= mgs_disk1_scenes_us[i][0]) && (track <= mgs_disk1_scenes_us[i][1])) {
				hit = mgs_disk1_scenes_us[i][2];
				break;
			}
		}
	}

	if (hit) {
		set_scenes(hit);
	}
	else {
		set_scenes(NO_SCENES);
	}
}

int wa_jp[][2] = {
		{0x385031,0x411234}
};
int wa_us[][2] = {
		{0x385011,0x411741}
};

void check_scenesforSPU(unsigned char arg1, unsigned char arg2, unsigned char arg3) {

	int i, hit = 0;
	int track = arg1 << 16 | arg2 << 8 | arg3;

	if (isTitleName(WILD_ARMS_US)) {
		for (i = 0; i < sizeof(wa_us) / sizeof(wa_us[0]); i++) {
			if ((track >= wa_us[i][0]) && (track <= wa_us[i][1])) {
				hit = 1;
				break;
			}
		}
	}
	else if (isTitleName(WILD_ARMS_JP)) {
		for (i = 0; i < sizeof(wa_jp) / sizeof(wa_jp[0]); i++) {
			if ((track >= wa_jp[i][0]) && (track <= wa_jp[i][1])) {
				hit = 1;
				break;
			}
		}
	}

	if (hit) {
		scenes = 1;
	}
	else {
		scenes = 0;
	}
}

