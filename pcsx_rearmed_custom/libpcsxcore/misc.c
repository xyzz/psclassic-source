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
 *   51 Franklin Street, Fifth Floor, Boston, MA 02111-1307 USA.           *
 ***************************************************************************/

/*
* Miscellaneous functions, including savestates and CD-ROM loading.
*/

#include "misc.h"
#include "cdrom.h"
#include "mdec.h"
#include "gpu.h"
#include "ppf.h"
#include "title.h"
#include <zlib.h>
#include "../frontend/menu.h"
#include "../frontend/main.h"
#include <dirent.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

char CdromId[10] = "";
char CdromId_old[10] = "";
char CdromLabel[33] = "";
char CdromLabel_old[33] = "";
char CdromPath[MAXPATHLEN] = "";
char CdromPath_old[MAXPATHLEN] = "";

int disc_change_type = 0;
static pthread_mutex_t statefile_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t statefile_thread = (pthread_t)0;
int time_to_sync_state = 0;

#define EXCLUSION_CONTROL

// PSX Executable types
#define PSX_EXE     1
#define CPE_EXE     2
#define COFF_EXE    3
#define INVALID_EXE 4

#define ISODCL(from, to) (to - from + 1)
#define MAX_ERROR_LEN 1024
#define MAX_STATE_PATH_LEN 64 // sufficient size in the current operation

struct error_info {
	int id;
	char message[MAX_ERROR_LEN];
};

struct iso_directory_record {
	char length			[ISODCL (1, 1)]; /* 711 */
	char ext_attr_length		[ISODCL (2, 2)]; /* 711 */
	char extent			[ISODCL (3, 10)]; /* 733 */
	char size			[ISODCL (11, 18)]; /* 733 */
	char date			[ISODCL (19, 25)]; /* 7 by 711 */
	char flags			[ISODCL (26, 26)];
	char file_unit_size		[ISODCL (27, 27)]; /* 711 */
	char interleave			[ISODCL (28, 28)]; /* 711 */
	char volume_sequence_number	[ISODCL (29, 32)]; /* 723 */
	unsigned char name_len		[ISODCL (33, 33)]; /* 711 */
	char name			[1];
};

// Save State.
#define AUTO_SAVE_TO_HEAP_SECOND (2)
#define AUTO_SAVE_TO_FILE_COUNT	 ((10/AUTO_SAVE_TO_HEAP_SECOND) + 1)
#define BLOCKING_TIME		 (10)

static struct timespec start_time = {0, 0};

typedef struct {
	int enable;
	int counting;
	int num;
} disc_change_state;

enum STATUS_RUNING{
	NOT_BUFF_INITIALIZED = 0,	/* status: not get memory */
	BUFF_INITIALIZED,			/* status: memory is ready ,only menu setting is ON */
	CONFIG_SET_OFF				/* status: when menu setting is OFF */
};

typedef struct {
	unsigned char*	Buff;
	int 		Size;
}data_buff_t;

typedef struct {
	data_buff_t 	 ScreenPic;
	data_buff_t 	 BIOS;
	data_buff_t 	 GPU;
	data_buff_t 	 SPU;			/* not write to file */
	data_buff_t 	 SPU1;			/* size is not const */
	data_buff_t	 SIO;
	data_buff_t	 CDR;
	data_buff_t	 PSXHW;
	data_buff_t	 PSXRCNT;
	data_buff_t	 MDEC;
	data_buff_t 	 NewDyna;		/* size is not const */
	int		 iNewDynaValidDataSize;
	int				 Num;
}state_data_t;

static state_data_t g_stateData[AUTO_SAVE_TO_FILE_COUNT];
static disc_change_state dcstateData[AUTO_SAVE_TO_FILE_COUNT] = {0};
static int gLastCount = 0;
static int gFilledNum = 0;
static int gBuffInitialized = NOT_BUFF_INITIALIZED;
static int resume_play = 0;
static int blocking_count = 0;
int memcardResetFlag = 0;
unsigned int memcardFlagOld = 0;

static char stateid[AUTO_SAVE_TO_FILE_COUNT][10];
int isUnknownCdrom = 1;
int holdResetEvent = 0;

void LogPrint(char* title1, int data){
        struct timeval myTime;
        gettimeofday(&myTime, NULL);
        printf("[%d.%6d] :%s, %d \n", myTime.tv_sec, myTime.tv_usec,title1, data );
}
#define xprintf  	//printf
#define LOG_Print 	//LogPrint

static int lock_statefile_mutex(void)
{
#ifdef EXCLUSION_CONTROL
  int ret;

  ret = pthread_mutex_lock(&statefile_mutex);
  if (ret != 0) {
    printf("ERROR: failed to lock the mutex\n");
    return -1;
  }
#endif
  return 0;
}

static int unlock_statefile_mutex(void)
{
#ifdef EXCLUSION_CONTROL
  int ret;

  ret = pthread_mutex_unlock(&statefile_mutex);
  if (ret != 0) {
    printf("ERROR: failed to unlock the mutex\n");
    return -1;
  }
#endif
  return 0;
}

static int write_statefile(struct error_info *err)
{
  pid_t pid;
  int status_num = 1;
  int fd;
  struct dirent **entry_list;
  int entry_num;
  int i, ret;
  char file_name[MAX_STATE_PATH_LEN], buff[MAX_ERROR_LEN];
  char *ext;

  int error_id;
  char error_msg[MAX_ERROR_LEN];

  error_id = err->id;
  strcpy(error_msg, err->message);
  free(err);

  ret = lock_statefile_mutex();
  if (ret < 0) {
    return -1;
  }

  entry_num = scandir(STATUS_DIR, &entry_list, NULL, alphasort);
  for (i=0; i<entry_num; i++) {
    ext = strrchr(entry_list[i]->d_name, '.');
    ret = strcmp(ext, ".sts");
    if (ret == 0) {
      status_num++;
    }
  }
  sprintf(buff, "%03d.sts", status_num);
  sprintf(file_name, "%s%s", STATUS_DIR, buff);
  fd = open(file_name, O_WRONLY | O_CREAT, 0644);
  if (fd < 0) {
    printf("ERROR: failed to open a state file:%s\n", file_name);
    unlock_statefile_mutex();
    return -1;
  }

  sprintf(buff, "%d\n%s", error_id, error_msg);
  ret = write(fd, buff, strlen(buff));
  if (fd < 0) {
    printf("ERROR: failed to write a state file:%s\n", file_name);
    close(fd);
    unlock_statefile_mutex();
    return -1;
  }

  fsync(fd);
  close(fd);
  unlock_statefile_mutex();

  return 0;
}

int save_error(int error_id, char *error_msg)
{
  int ret;
  struct error_info *err;

  err = malloc(sizeof(struct error_info));
  bzero(err, sizeof(struct error_info));
  err->id = error_id;
  strncpy(err->message, error_msg, MAX_ERROR_LEN-1);

  pthread_attr_t thread_attr;
  pthread_attr_init(&thread_attr);
  pthread_attr_setdetachstate(&thread_attr , PTHREAD_CREATE_DETACHED);

  ret = pthread_create(&statefile_thread, &thread_attr, write_statefile, err);
  pthread_attr_destroy(&thread_attr);

  return ret;
}

static int setTileScreenAdjust(){
  int ret = isTitleName(COLIN_MCRAE_RALLY_EU)
            || isTitleName(CRASH_BANDICOOT_2_EU)
            || isTitleName(CRASH_BANDICOOT_2_JP)
            || isTitleName(CRASH_BANDICOOT_2_US)
            || isTitleName(DESTRUCTION_DERBY_EU)
            || isTitleName(DESTRUCTION_DERBY_US)
            || isTitleName(DISNEY_TOY_STORY_2_EU)
            || isTitleName(DRIVER_EU)
            || isTitleName(DRIVER_US)
            || isTitleName(EHRGEIZ_JP)
            || isTitleName(FIGHTING_FORCE_US)
            || isTitleName(GRAND_THEFT_AUTO_2_EU)
            || isTitleName(GRAND_THEFT_AUTO_2_US)
            || isTitleName(HARRY_POTTER_AND_THE_PHILOSOPHERS_STONE_EU)
            || isTitleName(KLONOA_DOOR_TO_PHANTAMILE_JP)
            || isTitleName(KLONOA_DOOR_TO_PHANTAMILE_US)
            || isTitleName(KULA_WORLD_EU)
            || isTitleName(MEDIEVIL_EU)
            || isTitleName(MEDIEVIL_US)
            || isTitleName(MR_DRILLER_EU)
            || isTitleName(MR_DRILLER_G_JP)
            || isTitleName(MR_DRILLER_JP)
            || isTitleName(MR_DRILLER_US)
            || isTitleName(PARASITE_EVE_DISC_1_JP)
            || isTitleName(PARASITE_EVE_DISC_1_US)
            || isTitleName(PARASITE_EVE_DISC_2_JP)
            || isTitleName(PARASITE_EVE_DISC_2_US)
            || isTitleName(RAY_STORM_JP)
            || isTitleName(RIDGE_RACER_TYPE_4_EU)
            || isTitleName(RIDGE_RACER_TYPE_4_JP)
            || isTitleName(RIDGE_RACER_TYPE_4_US)
            || isTitleName(SILENT_HILL_EU)
            || isTitleName(SILENT_HILL_JP)
            || isTitleName(SILENT_HILL_US)
            || isTitleName(SPEC_OPS_STEALTH_PATROL_US)
            || isTitleName(STREET_FIGHTER_ALPHA_3_US)
            || isTitleName(STREET_FIGHTER_EX_PLUS_EU)
            || isTitleName(STREET_FIGHTER_EX_PLUS_JP)
            || isTitleName(STREET_FIGHTER_EX_PLUS_US)
            || isTitleName(TEKKEN3_JP)
            || isTitleName(TOM_CLANCYS_RAINBOW_SIX_EU)
            || isTitleName(TOMB_RAIDER_2_EU)
            || isTitleName(TOMB_RAIDER_2_JP)
            || isTitleName(TOMB_RAIDER_2_US)
            || isTitleName(TOMB_RAIDER_EU)
            || isTitleName(TOMB_RAIDER_JP)
            || isTitleName(TOMB_RAIDER_US)
            || isTitleName(TOMBA_JP)
            || isTitleName(TOMBA_US)
            || isTitleName(XEVIOUS_3D_G_JP)
            || isTitleName(XEVIOUS_3D_G_US);

  if(GPU_setPatchFlag)
	GPU_setPatchFlag(GPU_PATCH_SCREEN_ADJUST, ret);

  return ret;
}

static int setTitleIsFF7(){
  int ret = isTitleName(FINAL_FANTANSY_VII_DICS_1_EU)
            || isTitleName(FINAL_FANTANSY_VII_DICS_1_JP)
            || isTitleName(FINAL_FANTANSY_VII_DICS_1_US)
            || isTitleName(FINAL_FANTANSY_VII_DICS_2_EU)
            || isTitleName(FINAL_FANTANSY_VII_DICS_2_JP)
            || isTitleName(FINAL_FANTANSY_VII_DICS_2_US)
            || isTitleName(FINAL_FANTANSY_VII_DICS_3_EU)
            || isTitleName(FINAL_FANTANSY_VII_DICS_3_JP)
            || isTitleName(FINAL_FANTANSY_VII_DICS_3_US)
            || isTitleName(FINAL_FANTANSY_VII_DICS_4_JP);

  if(GPU_setPatchFlag)
	GPU_setPatchFlag(GPU_PATCH_IS_FF7, ret);

  return ret;
}

static int setTitleIsMrDriller(){
  int ret = isTitleName(MR_DRILLER_EU)
            || isTitleName(MR_DRILLER_G_JP)
            || isTitleName(MR_DRILLER_JP)
            || isTitleName(MR_DRILLER_US);

  if(GPU_setPatchFlag)
	GPU_setPatchFlag(GPU_PATCH_IS_MR_DRILLER, ret);

  return ret;
}

static int setTitleIsMrDrillerJp(){
  int ret = isTitleName(MR_DRILLER_JP);

  if(GPU_setPatchFlag)
    GPU_setPatchFlag(GPU_PATCH_IS_MR_DRILLER_JP, ret);

  return ret;
}

static int setTitleAddVram2(){
  int ret = isTitleName(METAL_GEAR_SOLID_DISC_1_EU)
            || isTitleName(METAL_GEAR_SOLID_DISC_1_JP)
            || isTitleName(METAL_GEAR_SOLID_DISC_1_US)
            || isTitleName(METAL_GEAR_SOLID_DISC_2_EU)
            || isTitleName(METAL_GEAR_SOLID_DISC_2_JP)
            || isTitleName(METAL_GEAR_SOLID_DISC_2_US);

  if(GPU_setPatchFlag)
	GPU_setPatchFlag(GPU_PATCH_ADD_VRAM2, ret);
  return ret;
}

static int setTitleBO(){
  int ret = isTitleName(METAL_GEAR_SOLID_DISC_1_JP)
            || isTitleName(METAL_GEAR_SOLID_DISC_1_US);

  if(GPU_setPatchFlag)
	GPU_setPatchFlag(GPU_PATCH_ADD_BO, ret);
  return ret;
}

static int setTitleIsARCTHELAD(){
  int ret = isTitleName(ARC_THE_LAD_JP)
            || isTitleName(ARC_THE_LAD_2_JP);

  if(GPU_setPatchFlag)
	GPU_setPatchFlag(GPU_PATCH_ARC_THE_LAD, ret);

  return ret;
}

int isTitleName(enum TITLE_NAME argTitleName)
{
  return (g_eTitleName == argTitleName) ? 1 : 0;
}

void initTitleName(void) {
  g_eTitleName = TITLE_NAME_NONE;
}

void setTitleName(void) {
  int i = 0;

  initTitleName();
  setCdromId();
  while(*(stTitleList[i].m_cpCdromId)) {
    if(strcmp(stTitleList[i].m_cpCdromId , CdromId) == 0) {
      g_eTitleName = stTitleList[i].m_eTitleName;
      break;
    }
    i++;
  }
  setTileScreenAdjust();
  setTitleIsFF7();
  setTitleIsMrDriller();
  setTitleIsMrDrillerJp();
  setTitleAddVram2();
  setTitleBO();
  setTitleIsARCTHELAD();
}

void setCdromId(void) {
	char * fileName = strrchr(GetIsoFile(), '/');
	int c = 0;
	for (int i = 0; i < strlen(fileName); ++i) {
		if (fileName[i] == '.' || c >= sizeof(CdromId) - 1) {
			break;
		}
		if (isalnum(fileName[i])) {
			CdromId[c++] = fileName[i];
		}
	}
}

void setDiscChangeType()
{
  int i, n, ret, cd_num;
  char title_dir_path[128];
  char *ext, *p;
  struct dirent **namelist;

  // get title directory path
  strcpy(title_dir_path, GetIsoFile());
  p = strrchr(title_dir_path, '/');
  if (p != NULL) {
    *p = 0;
  }

  // count number of .cue file
  n = scandir(title_dir_path, &namelist, NULL, NULL);
  cd_num = 0;
  for (i=0; i<n; i++) {
    ext = strrchr(namelist[i]->d_name, '.');
    ret = strcmp(ext, ".cue");
    if (ret == 0) {
      cd_num++;
    }
  }

  if (cd_num <= 1) {
    disc_change_type = 0;
  }
#if 0
  else if (isTitleName(DUMMY_TITLE_1)) {
    disc_change_type = 2;
  }
  else if (isTitleName(DUMMY_TITLE_2)) {
    disc_change_type = 3;
  }
  else if (isTitleName(DUMMY_TITLE_3)) {
    disc_change_type = 4;
  }
  else if (isTitleName(DUMMY_TITLE_4)) {
    disc_change_type = 5;
  }
#endif 
 else {
    disc_change_type = 1;
  }

  return;
}

void mmssdd( char *b, char *p )
{
	int m, s, d;
#if defined(__arm__)
	unsigned char *u = (void *)b;
	int block = (u[3] << 24) | (u[2] << 16) | (u[1] << 8) | u[0];
#elif defined(__BIGENDIAN__)
	int block = (b[0] & 0xff) | ((b[1] & 0xff) << 8) | ((b[2] & 0xff) << 16) | (b[3] << 24);
#else
	int block = *((int*)b);
#endif

	block += 150;
	m = block / 4500;			// minutes
	block = block - m * 4500;	// minutes rest
	s = block / 75;				// seconds
	d = block - s * 75;			// seconds rest

	m = ((m / 10) << 4) | m % 10;
	s = ((s / 10) << 4) | s % 10;
	d = ((d / 10) << 4) | d % 10;	

	p[0] = m;
	p[1] = s;
	p[2] = d;
}

#define incTime() \
	time[0] = btoi(time[0]); time[1] = btoi(time[1]); time[2] = btoi(time[2]); \
	time[2]++; \
	if(time[2] == 75) { \
		time[2] = 0; \
		time[1]++; \
		if (time[1] == 60) { \
			time[1] = 0; \
			time[0]++; \
		} \
	} \
	time[0] = itob(time[0]); time[1] = itob(time[1]); time[2] = itob(time[2]);

#define READTRACK() \
	if (CDR_readTrack(time) == -1) return -1; \
	buf = (void *)CDR_getBuffer(); \
	if (buf == NULL) return -1; \
	else CheckPPFCache((u8 *)buf, time[0], time[1], time[2]);

#define READDIR(_dir) \
	READTRACK(); \
	memcpy(_dir, buf + 12, 2048); \
 \
	incTime(); \
	READTRACK(); \
	memcpy(_dir + 2048, buf + 12, 2048);

void StartCheckOpen(void) {
	clock_gettime(CLOCK_MONOTONIC, &start_time);
}

int CheckOpenEnabled(void) {
	struct timespec current_time;

	clock_gettime(CLOCK_MONOTONIC, &current_time);
	if (resume_play || current_time.tv_sec - start_time.tv_sec > open_invalid_time) {
		return 1;
	}
	return 0;
}

int GetCdromFile(u8 *mdir, u8 *time, char *filename) {
	struct iso_directory_record *dir;
	int retval = -1;
	u8 ddir[4096];
	u8 *buf;
	int i;

	// only try to scan if a filename is given
	if (!strlen(filename)) return -1;

	i = 0;
	while (i < 4096) {
		dir = (struct iso_directory_record*) &mdir[i];
		if (dir->length[0] == 0) {
			return -1;
		}
		i += (u8)dir->length[0];

		if (dir->flags[0] & 0x2) { // it's a dir
			if (!strnicmp((char *)&dir->name[0], filename, dir->name_len[0])) {
				if (filename[dir->name_len[0]] != '\\') continue;

				filename += dir->name_len[0] + 1;

				mmssdd(dir->extent, (char *)time);
				READDIR(ddir);
				i = 0;
				mdir = ddir;
			}
		} else {
			if (!strnicmp((char *)&dir->name[0], filename, strlen(filename))) {
				mmssdd(dir->extent, (char *)time);
				retval = 0;
				break;
			}
		}
	}
	return retval;
}

static const unsigned int gpu_ctl_def[] = {
	0x00000000, 0x01000000, 0x03000000, 0x04000000,
	0x05000800, 0x06c60260, 0x0703fc10, 0x08000027,
};

static const unsigned int gpu_data_def[] = {
	0xe100360b, 0xe2000000, 0xe3000800, 0xe4077e7f,
	0xe5001000, 0xe6000000,
	0x02000000, 0x00000000, 0x01ff03ff,
};

static void fake_bios_gpu_setup(void)
{
	int i;

	for (i = 0; i < sizeof(gpu_ctl_def) / sizeof(gpu_ctl_def[0]); i++)
		GPU_writeStatus(gpu_ctl_def[i]);

	for (i = 0; i < sizeof(gpu_data_def) / sizeof(gpu_data_def[0]); i++)
		GPU_writeData(gpu_data_def[i]);
}

int LoadCdrom() {
	EXE_HEADER tmpHead;
	struct iso_directory_record *dir;
	u8 time[4], *buf;
	u8 mdir[4096];
	char exename[256];

	// not the best place to do it, but since BIOS boot logo killer
	// is just below, do it here
	fake_bios_gpu_setup();

	if (!Config.HLE) {
		// skip BIOS logos
		//psxRegs.pc = psxRegs.GPR.n.ra;
		return 0;
	}

	time[0] = itob(0); time[1] = itob(2); time[2] = itob(0x10);

	READTRACK();

	// skip head and sub, and go to the root directory record
	dir = (struct iso_directory_record*) &buf[12+156]; 

	mmssdd(dir->extent, (char*)time);

	READDIR(mdir);

	// Load SYSTEM.CNF and scan for the main executable
	if (GetCdromFile(mdir, time, "SYSTEM.CNF;1") == -1) {
		// if SYSTEM.CNF is missing, start an existing PSX.EXE
		if (GetCdromFile(mdir, time, "PSX.EXE;1") == -1) return -1;

		READTRACK();
	}
	else {
		// read the SYSTEM.CNF
		READTRACK();

		sscanf((char *)buf + 12, "BOOT = cdrom:\\%255s", exename);
		if (GetCdromFile(mdir, time, exename) == -1) {
			sscanf((char *)buf + 12, "BOOT = cdrom:%255s", exename);
			if (GetCdromFile(mdir, time, exename) == -1) {
				char *ptr = strstr((char *)buf + 12, "cdrom:");
				if (ptr != NULL) {
					ptr += 6;
					while (*ptr == '\\' || *ptr == '/') ptr++;
					strncpy(exename, ptr, 255);
					exename[255] = '\0';
					ptr = exename;
					while (*ptr != '\0' && *ptr != '\r' && *ptr != '\n') ptr++;
					*ptr = '\0';
					if (GetCdromFile(mdir, time, exename) == -1)
						return -1;
				} else
					return -1;
			}
		}

		// Read the EXE-Header
		READTRACK();
	}

	memcpy(&tmpHead, buf + 12, sizeof(EXE_HEADER));

	psxRegs.pc = SWAP32(tmpHead.pc0);
	psxRegs.GPR.n.gp = SWAP32(tmpHead.gp0);
	psxRegs.GPR.n.sp = SWAP32(tmpHead.s_addr); 
	if (psxRegs.GPR.n.sp == 0) psxRegs.GPR.n.sp = 0x801fff00;

	tmpHead.t_size = SWAP32(tmpHead.t_size);
	tmpHead.t_addr = SWAP32(tmpHead.t_addr);

	psxCpu->Clear(tmpHead.t_addr, tmpHead.t_size / 4);

	// Read the rest of the main executable
	while (tmpHead.t_size & ~2047) {
		void *ptr = (void *)PSXM(tmpHead.t_addr);

		incTime();
		READTRACK();

		if (ptr != NULL) memcpy(ptr, buf+12, 2048);

		tmpHead.t_size -= 2048;
		tmpHead.t_addr += 2048;
	}

	return 0;
}

int LoadCdromFile(const char *filename, EXE_HEADER *head) {
	struct iso_directory_record *dir;
	u8 time[4],*buf;
	u8 mdir[4096];
	char exename[256];
	u32 size, addr;
	void *mem;

	sscanf(filename, "cdrom:\\%255s", exename);

	time[0] = itob(0); time[1] = itob(2); time[2] = itob(0x10);

	READTRACK();

	// skip head and sub, and go to the root directory record
	dir = (struct iso_directory_record *)&buf[12 + 156]; 

	mmssdd(dir->extent, (char*)time);

	READDIR(mdir);

	if (GetCdromFile(mdir, time, exename) == -1) return -1;

	READTRACK();

	memcpy(head, buf + 12, sizeof(EXE_HEADER));
	size = head->t_size;
	addr = head->t_addr;

	psxCpu->Clear(addr, size / 4);

	while (size & ~2047) {
		incTime();
		READTRACK();

		mem = PSXM(addr);
		if (mem)
			memcpy(mem, buf + 12, 2048);

		size -= 2048;
		addr += 2048;
	}

	return 0;
}

int CheckCdrom() {
	struct iso_directory_record *dir;
	unsigned char time[4];
	char *buf;
	unsigned char mdir[4096];
	char exename[256];
	int i, len, c;

	initTitleName();

	FreePPFCache();

	time[0] = itob(0);
	time[1] = itob(2);
	time[2] = itob(0x10);

	READTRACK();

	memset(CdromLabel, 0, sizeof(CdromLabel));
	memset(CdromId, 0, sizeof(CdromId));
	memset(exename, 0, sizeof(exename));

	strncpy(CdromLabel, buf + 52, 32);

	// skip head and sub, and go to the root directory record
	dir = (struct iso_directory_record *)&buf[12 + 156]; 

	mmssdd(dir->extent, (char *)time);

	READDIR(mdir);

	if (GetCdromFile(mdir, time, "SYSTEM.CNF;1") != -1) {
		READTRACK();

		sscanf(buf + 12, "BOOT = cdrom:\\%255s", exename);
		if (GetCdromFile(mdir, time, exename) == -1) {
			sscanf(buf + 12, "BOOT = cdrom:%255s", exename);
			if (GetCdromFile(mdir, time, exename) == -1) {
				char *ptr = strstr(buf + 12, "cdrom:");			// possibly the executable is in some subdir
				if (ptr != NULL) {
					ptr += 6;
					while (*ptr == '\\' || *ptr == '/') ptr++;
					strncpy(exename, ptr, 255);
					exename[255] = '\0';
					ptr = exename;
					while (*ptr != '\0' && *ptr != '\r' && *ptr != '\n') ptr++;
					*ptr = '\0';
					if (GetCdromFile(mdir, time, exename) == -1)
					 	return -1;		// main executable not found
				} else
					return -1;
			}
		}
	} else if (GetCdromFile(mdir, time, "PSX.EXE;1") != -1) {
		strcpy(exename, "PSX.EXE;1");
		strcpy(CdromId, "SLUS99999");
	} else
		return -1;		// SYSTEM.CNF and PSX.EXE not found

	char * fileName = strrchr(GetIsoFile(), '/');
	c = 0;
	for (i = 0; i < strlen(fileName); ++i) {
		if (fileName[i] == '.' || c >= sizeof(CdromId) - 1)
			break;
		if (isalnum(fileName[i]))
			CdromId[c++] = fileName[i];
	}

	if (CdromId[0] == '\0')
		strcpy(CdromId, "SLUS99999");

	if (Config.PsxAuto) { // autodetect system (pal or ntsc)
		if (CdromId[2] == 'e' || CdromId[2] == 'E')
			Config.PsxType = PSX_TYPE_PAL; // pal
		else Config.PsxType = PSX_TYPE_NTSC; // ntsc
	}

	if (CdromLabel[0] == ' ') {
		strncpy(CdromLabel, CdromId, 9);
	}
	SysPrintf(_("CD-ROM Label: %.32s\n"), CdromLabel);
	SysPrintf(_("CD-ROM ID: %.9s\n"), CdromId);
	SysPrintf(_("CD-ROM EXE Name: %.255s\n"), exename);

	strncpy(CdromPath, GetIsoFile(), sizeof(CdromPath));
	if (CdromPath_old[0] == '\0' || CdromLabel_old[0] == '\0' || CdromId_old[0] == '\0' || !(g_opts & OPT_AUTOSAVE)) {
			strncpy(CdromPath_old, CdromPath, sizeof(CdromPath));
			strncpy(CdromLabel_old, CdromLabel, sizeof(CdromLabel));
			strncpy(CdromId_old, CdromId, sizeof(CdromId));
	}
	if (holdResetEvent) {
		emu_set_action(SACTION_RESET_EVENT);
		holdResetEvent = 0;
	}
	isUnknownCdrom = 0;
	BuildPPFCache();

	setTitleName();

	setDiscChangeType();
	return 0;
}

static int PSXGetFileType(FILE *f) {
	unsigned long current;
	u8 mybuf[2048];
	EXE_HEADER *exe_hdr;
	FILHDR *coff_hdr;

	current = ftell(f);
	fseek(f, 0L, SEEK_SET);
	fread(mybuf, 2048, 1, f);
	fseek(f, current, SEEK_SET);

	exe_hdr = (EXE_HEADER *)mybuf;
	if (memcmp(exe_hdr->id, "PS-X EXE", 8) == 0)
		return PSX_EXE;

	if (mybuf[0] == 'C' && mybuf[1] == 'P' && mybuf[2] == 'E')
		return CPE_EXE;

	coff_hdr = (FILHDR *)mybuf;
	if (SWAPu16(coff_hdr->f_magic) == 0x0162)
		return COFF_EXE;

	return INVALID_EXE;
}

// temporary pandora workaround..
// FIXME: remove
size_t fread_to_ram(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	void *tmp;
	size_t ret = 0;
	
	tmp = malloc(size * nmemb);
	if (tmp) {
		ret = fread(tmp, size, nmemb, stream);
		memcpy(ptr, tmp, size * nmemb);
		free(tmp);
	}
	return ret;
}

int Load(const char *ExePath) {
	FILE *tmpFile;
	EXE_HEADER tmpHead;
	int type;
	int retval = 0;
	u8 opcode;
	u32 section_address, section_size;
	void *mem;

	strncpy(CdromId, "SLUS99999", 9);
	strncpy(CdromLabel, "SLUS_999.99", 11);

	tmpFile = fopen(ExePath, "rb");
	if (tmpFile == NULL) {
		SysPrintf(_("Error opening file: %s.\n"), ExePath);
		retval = -1;
	} else {
		type = PSXGetFileType(tmpFile);
		switch (type) {
			case PSX_EXE:
				fread(&tmpHead,sizeof(EXE_HEADER),1,tmpFile);
				section_address = SWAP32(tmpHead.t_addr);
				section_size = SWAP32(tmpHead.t_size);
				mem = PSXM(section_address);
				if (mem != NULL) {
					fseek(tmpFile, 0x800, SEEK_SET);		
					fread_to_ram(mem, section_size, 1, tmpFile);
					psxCpu->Clear(section_address, section_size / 4);
				}
				fclose(tmpFile);
				psxRegs.pc = SWAP32(tmpHead.pc0);
				psxRegs.GPR.n.gp = SWAP32(tmpHead.gp0);
				psxRegs.GPR.n.sp = SWAP32(tmpHead.s_addr); 
				if (psxRegs.GPR.n.sp == 0)
					psxRegs.GPR.n.sp = 0x801fff00;
				retval = 0;
				break;
			case CPE_EXE:
				fseek(tmpFile, 6, SEEK_SET); /* Something tells me we should go to 4 and read the "08 00" here... */
				do {
					fread(&opcode, 1, 1, tmpFile);
					switch (opcode) {
						case 1: /* Section loading */
							fread(&section_address, 4, 1, tmpFile);
							fread(&section_size, 4, 1, tmpFile);
							section_address = SWAPu32(section_address);
							section_size = SWAPu32(section_size);
#ifdef EMU_LOG
							EMU_LOG("Loading %08X bytes from %08X to %08X\n", section_size, ftell(tmpFile), section_address);
#endif
							mem = PSXM(section_address);
							if (mem != NULL) {
								fread_to_ram(mem, section_size, 1, tmpFile);
								psxCpu->Clear(section_address, section_size / 4);
							}
							break;
						case 3: /* register loading (PC only?) */
							fseek(tmpFile, 2, SEEK_CUR); /* unknown field */
							fread(&psxRegs.pc, 4, 1, tmpFile);
							psxRegs.pc = SWAPu32(psxRegs.pc);
							break;
						case 0: /* End of file */
							break;
						default:
							SysPrintf(_("Unknown CPE opcode %02x at position %08x.\n"), opcode, ftell(tmpFile) - 1);
							retval = -1;
							break;
					}
				} while (opcode != 0 && retval == 0);
				break;
			case COFF_EXE:
				SysPrintf(_("COFF files not supported.\n"));
				retval = -1;
				break;
			case INVALID_EXE:
				SysPrintf(_("This file does not appear to be a valid PSX EXE file.\n"));
				SysPrintf(_("(did you forget -cdfile ?)\n"));
				retval = -1;
				break;
		}
	}

	if (retval != 0) {
		CdromId[0] = '\0';
		CdromLabel[0] = '\0';
	}

	return retval;
}

static void *fadein(void* param) {
	SPU_fadein();

	return;
}

// STATES

static void *zlib_open(const char *name, const char *mode)
{
	return gzopen(name, mode);
}

static int zlib_read(void *file, void *buf, u32 len)
{
	return gzread(file, buf, len);
}

static int zlib_write(void *file, const void *buf, u32 len)
{
	return gzwrite(file, buf, len);
}

static long zlib_seek(void *file, long offs, int whence)
{
	return gzseek(file, offs, whence);
}

static void zlib_close(void *file)
{
	gzclose(file);
}

struct PcsxSaveFuncs SaveFuncs = {
	zlib_open, zlib_read, zlib_write, zlib_seek, zlib_close
};

static const char PcsxHeader[32] = "STv4 PCSX v" PACKAGE_VERSION;

// Savestate Versioning!
// If you make changes to the savestate version, please increment the value below.
static const u32 SaveVersion = 0x8b410006;

int SaveState(const char *file) {
	void *f;
	GPUFreeze_t *gpufP;
	SPUFreeze_t *spufP;
	int Size;
	unsigned char *pMem;

	f = SaveFuncs.open(file, "wb");
	if (f == NULL) return -1;
	xprintf("SaveState  to file [%s] \n", file);
	new_dyna_before_save();

	SaveFuncs.write(f, (void *)PcsxHeader, 32);
	SaveFuncs.write(f, (void *)&SaveVersion, sizeof(u32));
	SaveFuncs.write(f, (void *)&Config.HLE, sizeof(boolean));

	pMem = (unsigned char *)malloc(128 * 96 * 3);
	if (pMem == NULL) return -1;
	GPU_getScreenPic(pMem);
	SaveFuncs.write(f, pMem, 128 * 96 * 3);
	free(pMem);

	if (Config.HLE)
		psxBiosFreeze(1);

	SaveFuncs.write(f, psxM, 0x00200000);
	SaveFuncs.write(f, psxR, 0x00080000);
	SaveFuncs.write(f, psxH, 0x00010000);
	SaveFuncs.write(f, (void *)&psxRegs, sizeof(psxRegs));

	// gpu
	gpufP = (GPUFreeze_t *)malloc(sizeof(GPUFreeze_t));
	gpufP->ulFreezeVersion = 1;
	GPU_freeze(1, gpufP);
	SaveFuncs.write(f, gpufP, sizeof(GPUFreeze_t));
	free(gpufP);

	// spu
	spufP = (SPUFreeze_t *) malloc(16);
	SPU_freeze(2, spufP, psxRegs.cycle);
	Size = spufP->Size; SaveFuncs.write(f, &Size, 4);
	free(spufP);
	spufP = (SPUFreeze_t *) malloc(Size);
	SPU_freeze(1, spufP, psxRegs.cycle);
	SaveFuncs.write(f, spufP, Size);
	free(spufP);

	sioFreeze(f, 1);
	cdrFreeze(f, 1);
	psxHwFreeze(f, 1);
	psxRcntFreeze(f, 1);
	mdecFreeze(f, 1);
	new_dyna_freeze(f, 1);

	// disc change state
	disc_change_state current_state = {is_disc_change, is_nop_count, nop_cnt};
	SaveFuncs.write(f, &current_state, sizeof(disc_change_state));

	int fd = fileno(f);
	fsync(fd);
	SaveFuncs.close(f);

	new_dyna_after_save();

	return 0;
}

state_data_t* getSaveStateArray(int count) {
	if (count < 0 || count >= AUTO_SAVE_TO_FILE_COUNT) return NULL;

	state_data_t* buff = (state_data_t* )&g_stateData[count];
	return buff;
}

int SaveStateWork(void * fname) {

	xprintf("SaveStateWork g_opts & OPT_AUTOSAVE  [%d] \n", g_opts & OPT_AUTOSAVE);
	if ((g_opts & OPT_AUTOSAVE) == 0) {
		return SaveState(fname);
	}
	int old_index;

	if (gFilledNum <= 0) {
		xprintf("SaveStateWork gFilledNum  [%d] \n", gFilledNum);
		return -1;
	}
	else if (gFilledNum < AUTO_SAVE_TO_FILE_COUNT) {
		if (resume_play) {
			return -1;
		}
		old_index = 0;
	}
	else {
		if (gLastCount < AUTO_SAVE_TO_FILE_COUNT) {
			old_index = gLastCount;
		}
		else {
			old_index = 0;
		}
	}

	xprintf("SaveStateWork old_index  [%d] , gLastCount [%d], gFilledNum[%d] \n", old_index, gLastCount, gFilledNum);

	void *f = SaveFuncs.open(fname, "wb");
	if (f == NULL) {
		printf("SaveStateWork file open failed!! [%s] \n", fname);
		return -1;
	}

	state_data_t * pData = getSaveStateArray(old_index);
	if (pData == NULL) {
		printf("SaveStateWork  getSaveStateArray  failed!![%d] \n", old_index);
		return -1;
	}
	disc_change_state save_state = dcstateData[old_index];

	if (pData->ScreenPic.Buff) 	SaveFuncs.write(f, (void *)pData->ScreenPic.Buff, pData->ScreenPic.Size);
	if (pData->BIOS.Buff) 		SaveFuncs.write(f, (void *)pData->BIOS.Buff, pData->BIOS.Size);
	if (pData->GPU.Buff) 		SaveFuncs.write(f, (void *)pData->GPU.Buff, pData->GPU.Size);
	if (pData->SPU.Buff) 		SaveFuncs.write(f, (void *)pData->SPU.Buff, pData->SPU.Size);
	if (pData->SPU1.Buff) 		SaveFuncs.write(f, (void *)pData->SPU1.Buff, pData->SPU1.Size);
	if (pData->SIO.Buff) 		SaveFuncs.write(f, (void *)pData->SIO.Buff, pData->SIO.Size);
	if (pData->CDR.Buff) 		SaveFuncs.write(f, (void *)pData->CDR.Buff, pData->CDR.Size);
	if (pData->PSXHW.Buff) 		SaveFuncs.write(f, (void *)pData->PSXHW.Buff, pData->PSXHW.Size);
	if (pData->PSXRCNT.Buff) 	SaveFuncs.write(f, (void *)pData->PSXRCNT.Buff, pData->PSXRCNT.Size);
	if (pData->MDEC.Buff) 		SaveFuncs.write(f, (void *)pData->MDEC.Buff, pData->MDEC.Size);
	if (pData->NewDyna.Buff) 	SaveFuncs.write(f, (void *)pData->NewDyna.Buff, pData->iNewDynaValidDataSize);

	xprintf("SaveStateWork ScreenPic [%d] \n", pData->ScreenPic.Size);
	xprintf("SaveStateWork BIOS      [%d] \n", pData->BIOS.Size);
	xprintf("SaveStateWork GPU       [%d] \n", pData->GPU.Size);
	xprintf("SaveStateWork SPU       [%d] \n", pData->SPU.Size);
	xprintf("SaveStateWork SPU1      [%d] \n", pData->SPU1.Size);
	xprintf("SaveStateWork SIO 	 [%d] \n", pData->SIO.Size);
	xprintf("SaveStateWork CDR 	 [%d] \n", pData->CDR.Size);
	xprintf("SaveStateWork PSXHW 	 [%d] \n", pData->PSXHW.Size);
	xprintf("SaveStateWork PSXRCNT 	 [%d] \n", pData->PSXRCNT.Size);
	xprintf("SaveStateWork MDEC 	 [%d] \n", pData->MDEC.Size);
	xprintf("SaveStateWork NewDyna   [%d] \n", pData->NewDyna.Size);
	xprintf("SaveStateWork Num       [%d] \n", pData->Num);

	SaveFuncs.write(f, (void *)&save_state, sizeof(disc_change_state));

	int fd = fileno(f);
	fsync(fd);
	SaveFuncs.close(f);

	return 0;
}

int freeSaveStateMem(state_data_t * buff) {

	if (buff == NULL) return -1;

	if (buff->ScreenPic.Buff) 	free(buff->ScreenPic.Buff);
	if (buff->BIOS.Buff) 		free(buff->BIOS.Buff);
	if (buff->GPU.Buff)		free(buff->GPU.Buff);
	if (buff->SPU.Buff) 		free(buff->SPU.Buff);
	if (buff->SPU1.Buff) 		free(buff->SPU1.Buff);
	if (buff->SIO.Buff) 		free(buff->SIO.Buff);
	if (buff->CDR.Buff) 		free(buff->CDR.Buff);
	if (buff->PSXHW.Buff) 		free(buff->PSXHW.Buff);
	if (buff->PSXRCNT.Buff) 	free(buff->PSXRCNT.Buff);
	if (buff->MDEC.Buff) 		free(buff->MDEC.Buff);
	if (buff->NewDyna.Buff) 	free(buff->NewDyna.Buff);

	buff->ScreenPic.Buff = NULL;
	buff->BIOS.Buff = NULL;
	buff->GPU.Buff = NULL;
	buff->SPU.Buff = NULL;
	buff->SPU1.Buff = NULL;
	buff->SIO.Buff = NULL;
	buff->CDR.Buff = NULL;
	buff->PSXHW.Buff = NULL;
	buff->PSXRCNT.Buff = NULL;
	buff->MDEC.Buff = NULL;
	buff->NewDyna.Buff = NULL;

	return 0;
}

int SetCdromId(void) {
	int oldest_index = 0;
	int ret;

	if (gFilledNum < 0) {
		return -1;
	}
	else if (gFilledNum < AUTO_SAVE_TO_FILE_COUNT - 1) {
		oldest_index = 0;
	}
	else {
		oldest_index = gLastCount + 1;
		if (oldest_index >= AUTO_SAVE_TO_FILE_COUNT) {
			oldest_index = 0;
		}
	}

	ret = strncmp(stateid[oldest_index], CdromId, sizeof(CdromId));
	if (!ret) {
		ret = strncmp(CdromId_old, CdromId, sizeof(CdromId));
		if (ret) {
			strncpy(CdromPath_old, CdromPath, sizeof(CdromPath));
			strncpy(CdromLabel_old, CdromLabel, sizeof(CdromLabel));
			strncpy(CdromId_old, CdromId, sizeof(CdromId));
		}
	}

	return 0;
}

int AutoSaveState(int count) {
	int Size;
	unsigned char *pMem;
	if (count >= AUTO_SAVE_TO_FILE_COUNT || count < 0)
		return -1;

	state_data_t * pStateData = getSaveStateArray(count);
	if (pStateData == NULL)
		return -1;

	new_dyna_before_save();

	pMem = pStateData->ScreenPic.Buff;
	memcpy(pMem, (unsigned char *)PcsxHeader, 32);
	pMem += 32;
	memcpy(pMem, (unsigned char *)&SaveVersion, sizeof(u32));
	pMem += sizeof(u32);
	memcpy(pMem, (unsigned char *)&Config.HLE, sizeof(boolean));
	pMem += sizeof(boolean);
	GPU_getScreenPic(pMem);


	if (Config.HLE)
		psxBiosFreeze(1);

	pMem = pStateData->BIOS.Buff;
	memcpy(pMem, (unsigned char *)psxM, 0x00200000);
	pMem += 0x00200000;
	memcpy(pMem, (unsigned char *)psxR, 0x00080000);
	pMem += 0x00080000;
	memcpy(pMem, (unsigned char *)psxH, 0x00010000);
	pMem += 0x00010000;
	memcpy(pMem, (unsigned char *)&psxRegs, sizeof(psxRegs));

	// gpu
	GPUFreeze_t *gpufP = (GPUFreeze_t *)pStateData->GPU.Buff;
	gpufP->ulFreezeVersion = 1;
	GPU_freeze(1, gpufP);

	// spu
	char ca[16];
	SPUFreeze_t *spufP = (SPUFreeze_t *) ca;
	SPU_freeze(2, spufP, psxRegs.cycle);
	Size = spufP->Size;
	memcpy(pStateData->SPU.Buff, &Size, pStateData->SPU.Size);

	spufP = (SPUFreeze_t *) pStateData->SPU1.Buff;
	SPU_freeze(1, spufP, psxRegs.cycle);
	
	sioFreeze(pStateData->SIO.Buff, 2);
	cdrFreeze(pStateData->CDR.Buff, 2);
	psxHwFreeze(pStateData->PSXHW.Buff, 2);
	psxRcntFreeze(pStateData->PSXRCNT.Buff, 2);
	mdecFreeze(pStateData->MDEC.Buff, 2);
	
        pStateData->iNewDynaValidDataSize = new_dyna_freeze(pStateData->NewDyna.Buff, 2);

	xprintf("AutoSaveState ScreenPic	[%d] \n", pStateData->ScreenPic.Size);
	xprintf("AutoSaveState BIOS 		[%d] \n", pStateData->BIOS.Size);
	xprintf("AutoSaveState GPU 		[%d] \n", pStateData->GPU.Size);
	xprintf("AutoSaveState SPU 		[%d] \n", pStateData->SPU.Size);
	xprintf("AutoSaveState SPU1 		[%d] \n", pStateData->SPU1.Size);
	xprintf("AutoSaveState NewDyna 		[%d] \n", pStateData->iNewDynaValidDataSize);
	xprintf("AutoSaveState Num 		[%d] \n", pStateData->Num);

	disc_change_state current_state = {is_disc_change, is_nop_count, nop_cnt};
	dcstateData[count] = current_state;

	if (CdromId[0] != '\0') {
		strncpy(stateid[count], CdromId, sizeof(CdromId));
	}
	else {
		strncpy(stateid[count], CdromId_old, sizeof(CdromId_old));
	}
	SetCdromId();

	new_dyna_after_save();
	return 0;
}

int InitAutoSave(void) {
	int ret = 0;
	gFilledNum = 0;
	gLastCount = 0;
	memset((unsigned char *)g_stateData, 0, sizeof(g_stateData));

	state_data_t * pStateData = NULL;
	for (int i=0;i<AUTO_SAVE_TO_FILE_COUNT;i++) {
		pStateData = getSaveStateArray(i);
		if (pStateData == NULL) {
			ret = -1;
			break;
		}
		freeSaveStateMem(pStateData);

		int size;
		unsigned char *pMem;

		size = 32 + sizeof(u32) + sizeof(boolean) + 128 * 96 * 3;
		pMem = (unsigned char *)malloc(size);
		if (pStateData == NULL) {
			ret = -1;
			break;
		}

		pStateData->ScreenPic.Buff = pMem;
		pStateData->ScreenPic.Size = size;

		size = 0x00200000 + 0x00080000 + 0x00010000 + sizeof(psxRegs);
		pMem = (unsigned char *)malloc(size);
		if (pMem == NULL) {
			ret = -1;
			break;
		}

		pStateData->BIOS.Buff = pMem;
		pStateData->BIOS.Size = size;

		size = sizeof(GPUFreeze_t);
		pMem = (unsigned char *)malloc(size);
		if (pMem == NULL) {
			ret = -1;
			break;
		}
		pStateData->GPU.Buff = pMem;
		pStateData->GPU.Size = size;

		size = 4;
		pMem = (unsigned char *)malloc(size);
		if (pMem == NULL) {
			ret = -1;
			break;
		}

		pStateData->SPU.Buff = pMem;
		pStateData->SPU.Size = size;

		pStateData->SPU1.Size = SPU_freeze(2, (void *)0, 0);
		pStateData->SPU1.Buff = (unsigned char *)malloc(pStateData->SPU1.Size);
		if (pStateData->SPU1.Buff == NULL) {
			ret = -1;
			break;
		}
		
		pStateData->SIO.Size = sioFreeze((void *)0, 2);
		pStateData->SIO.Buff = (unsigned char *)malloc(pStateData->SIO.Size);
		if (pStateData->SIO.Buff == NULL) {
			ret = -1;
			break;
		}

		pStateData->CDR.Size = cdrFreeze((void *)0, 2);
		pStateData->CDR.Buff = (unsigned char *)malloc(pStateData->CDR.Size);
		if (pStateData->CDR.Buff == NULL) {
			ret = -1;
			break;
		}

		pStateData->PSXHW.Size = psxHwFreeze((void *)0, 2);
		pStateData->PSXHW.Buff = (unsigned char *)malloc(pStateData->PSXHW.Size);
		if (pStateData->PSXHW.Buff == NULL) {
			ret = -1;
			break;
		}

		pStateData->PSXRCNT.Size = psxRcntFreeze((void *)0, 2);
		pStateData->PSXRCNT.Buff = (unsigned char *)malloc(pStateData->PSXRCNT.Size);
		if (pStateData->PSXRCNT.Buff == NULL) {
			ret = -1;
			break;
		}

		pStateData->MDEC.Size = mdecFreeze((void *)0, 2);
		pStateData->MDEC.Buff = (unsigned char *)malloc(pStateData->MDEC.Size);
		if (pStateData->MDEC.Buff == NULL) {
			ret = -1;
			break;
		}

		pStateData->NewDyna.Size = new_dyna_freeze((void *)0, 2);
		pStateData->NewDyna.Buff = (unsigned char *)malloc(pStateData->NewDyna.Size);
		if (pStateData->NewDyna.Buff == NULL) {
			ret = -1;
			break;
		}
		
		pStateData->Num = i;
	}

	if (ret == -1) {
		for (int i=0; i<AUTO_SAVE_TO_FILE_COUNT; i++) {
 			pStateData = getSaveStateArray(i);
			freeSaveStateMem(pStateData);
		}
		printf("InitAutoSave malloc failed! \n");
	}
	else {
		gBuffInitialized = BUFF_INITIALIZED;
		/* wait for 2s when starting */
		printf("InitAutoSave malloc OK! \n");
	}

	return ret;
}

void emu_sync_state(void) {
	static struct timespec formerTimeSpec = {0, 0};
	struct timespec currentTimeSpec;
	struct timespec intervalTimeSpec;

	if ((g_opts & OPT_AUTOSAVE) == 0) {
		if (BUFF_INITIALIZED == gBuffInitialized) {
			xprintf("OPT_AUTOSAVE OFF! \n");
			gLastCount = 0;
			gFilledNum = 0;
			gBuffInitialized = CONFIG_SET_OFF;
		}
		// check interval time
		clock_gettime(CLOCK_MONOTONIC, &currentTimeSpec);
		if((formerTimeSpec.tv_sec == 0) && (formerTimeSpec.tv_nsec == 0)) {
			memcpy(&formerTimeSpec, &currentTimeSpec, sizeof(struct timespec));
		}

		intervalTimeSpec.tv_sec = currentTimeSpec.tv_sec - formerTimeSpec.tv_sec;
		if((currentTimeSpec.tv_nsec - formerTimeSpec.tv_nsec) < 0){
			intervalTimeSpec.tv_sec --;
		}
	
		if(intervalTimeSpec.tv_sec < AUTO_SAVE_TO_HEAP_SECOND) {
			return;
		}
		memcpy(&formerTimeSpec, &currentTimeSpec, sizeof(struct timespec));
		if ((memcardFlag==0)&&(memcardFlagOld==0)&&(memcardResetFlag==1)) {
			emu_set_action(SACTION_RESET_EVENT);
			memcardResetFlag = 0;
		}
		memcardFlagOld = memcardFlag; //Memory Card Flag Save
		memcardFlag = 0; //Memory Card Flag Clear
		return;
	}
	if (NOT_BUFF_INITIALIZED == gBuffInitialized) {
		if (InitAutoSave() == -1) return;
	}
	else if (CONFIG_SET_OFF == gBuffInitialized) {
		xprintf("OPT_AUTOSAVE ON! \n");
		gBuffInitialized = BUFF_INITIALIZED;
	}

	// check interval time
	clock_gettime(CLOCK_MONOTONIC, &currentTimeSpec);
	if((formerTimeSpec.tv_sec == 0) && (formerTimeSpec.tv_nsec == 0)) {
		memcpy(&formerTimeSpec, &currentTimeSpec, sizeof(struct timespec));
	}

	intervalTimeSpec.tv_sec = currentTimeSpec.tv_sec - formerTimeSpec.tv_sec;
	if((currentTimeSpec.tv_nsec - formerTimeSpec.tv_nsec) < 0){
		intervalTimeSpec.tv_sec --;
	}
	
	if(intervalTimeSpec.tv_sec < AUTO_SAVE_TO_HEAP_SECOND) {
		return;
	}
	memcpy(&formerTimeSpec, &currentTimeSpec, sizeof(struct timespec));

	// Don't get the status while displaying the BIOS screen.
	if (!resume_play && AUTO_SAVE_TO_HEAP_SECOND * blocking_count < BLOCKING_TIME) {
		blocking_count++;
		return;
	}

	if (memcardFlag == 0) {
		time_to_sync_state = 1;
	}
	if ((memcardFlag==0)&&(memcardFlagOld==0)&&(memcardResetFlag==1)) {
		emu_set_action(SACTION_RESET_EVENT);
		memcardResetFlag = 0;
	}
	memcardFlagOld = memcardFlag;
	memcardFlag = 0;
}

void emu_sync_state2(void) {
	int count = gLastCount;
	LOG_Print("emu_sync_state start", count);
	if(AutoSaveState(count) == 0) {
		if (gFilledNum < AUTO_SAVE_TO_FILE_COUNT) {
			gFilledNum ++;
		}
		count += 1;
		if (count >= AUTO_SAVE_TO_FILE_COUNT) {
			count = 0;
		}
		gLastCount = count;
	}
	LOG_Print("emu_sync_state end", count);
}

int LoadState(const char *file) {
	void *f;
	GPUFreeze_t *gpufP;
	SPUFreeze_t *spufP;
	int Size;
	char header[32];
	u32 version;
	boolean hle;
	disc_change_state last_state;

	f = SaveFuncs.open(file, "rb");
	if (f == NULL) return -1;

	SaveFuncs.read(f, header, sizeof(header));
	SaveFuncs.read(f, &version, sizeof(u32));
	SaveFuncs.read(f, &hle, sizeof(boolean));
	if (strncmp("STv4 PCSX", header, 9) != 0 || version != SaveVersion) {
		SaveFuncs.close(f);
		return -1;
	}
	Config.HLE = hle;

	if (Config.HLE)
		psxBiosInit();

	psxCpu->Reset();
	SaveFuncs.seek(f, 128 * 96 * 3, SEEK_CUR);

	SaveFuncs.read(f, psxM, 0x00200000);
	SaveFuncs.read(f, psxR, 0x00080000);
	SaveFuncs.read(f, psxH, 0x00010000);
	SaveFuncs.read(f, (void *)&psxRegs, sizeof(psxRegs));

	if (Config.HLE)
		psxBiosFreeze(0);

	// gpu
	gpufP = (GPUFreeze_t *)malloc(sizeof(GPUFreeze_t));
	SaveFuncs.read(f, gpufP, sizeof(GPUFreeze_t));
	GPU_freeze(0, gpufP);
	free(gpufP);
	if (HW_GPU_STATUS == 0)
		HW_GPU_STATUS = GPU_readStatus();

	// spu
	SaveFuncs.read(f, &Size, 4);
	spufP = (SPUFreeze_t *)malloc(Size);
	SaveFuncs.read(f, spufP, Size);
	SPU_freeze(0, spufP, psxRegs.cycle);
	free(spufP);

	xprintf("LoadState spu Size [0x%d] \n", Size);

	sioFreeze(f, 0);
	cdrFreeze(f, 0);
	psxHwFreeze(f, 0);
	psxRcntFreeze(f, 0);
	mdecFreeze(f, 0);
	new_dyna_freeze(f, 0);

	// load disc change state
	SaveFuncs.read(f, &last_state, sizeof(disc_change_state));
	is_disc_change = last_state.enable;
	is_nop_count = last_state.counting;
	nop_cnt = last_state.num;

	SaveFuncs.close(f);

	if (g_opts & OPT_AUTOSAVE) {	/* reset auto save buff when load state*/
		gLastCount = 0;
		gFilledNum = 0;
		printf("LoadState reset auto save buff \n");
	}
	resume_play = 1;

	pthread_t fadein_thread;
	pthread_create(&fadein_thread, NULL, &fadein, NULL);

	return 0;
}

int CheckState(const char *file) {
	void *f;
	char header[32];
	u32 version;
	boolean hle;

	f = SaveFuncs.open(file, "rb");
	if (f == NULL) return -1;

	SaveFuncs.read(f, header, sizeof(header));
	SaveFuncs.read(f, &version, sizeof(u32));
	SaveFuncs.read(f, &hle, sizeof(boolean));

	SaveFuncs.close(f);

	if (strncmp("STv4 PCSX", header, 9) != 0 || version != SaveVersion)
		return -1;

	return 0;
}

// NET Function Helpers

int SendPcsxInfo() {
	if (NET_recvData == NULL || NET_sendData == NULL)
		return 0;

	NET_sendData(&Config.Xa, sizeof(Config.Xa), PSE_NET_BLOCKING);
	NET_sendData(&Config.Sio, sizeof(Config.Sio), PSE_NET_BLOCKING);
	NET_sendData(&Config.SpuIrq, sizeof(Config.SpuIrq), PSE_NET_BLOCKING);
	NET_sendData(&Config.RCntFix, sizeof(Config.RCntFix), PSE_NET_BLOCKING);
	NET_sendData(&Config.PsxType, sizeof(Config.PsxType), PSE_NET_BLOCKING);
	NET_sendData(&Config.Cpu, sizeof(Config.Cpu), PSE_NET_BLOCKING);

	return 0;
}

int RecvPcsxInfo() {
	int tmp;

	if (NET_recvData == NULL || NET_sendData == NULL)
		return 0;

	NET_recvData(&Config.Xa, sizeof(Config.Xa), PSE_NET_BLOCKING);
	NET_recvData(&Config.Sio, sizeof(Config.Sio), PSE_NET_BLOCKING);
	NET_recvData(&Config.SpuIrq, sizeof(Config.SpuIrq), PSE_NET_BLOCKING);
	NET_recvData(&Config.RCntFix, sizeof(Config.RCntFix), PSE_NET_BLOCKING);
	NET_recvData(&Config.PsxType, sizeof(Config.PsxType), PSE_NET_BLOCKING);

	SysUpdate();

	tmp = Config.Cpu;
	NET_recvData(&Config.Cpu, sizeof(Config.Cpu), PSE_NET_BLOCKING);
	if (tmp != Config.Cpu) {
		psxCpu->Shutdown();
#ifdef PSXREC
		if (Config.Cpu == CPU_INTERPRETER) psxCpu = &psxInt;
		else psxCpu = &psxRec;
#else
		psxCpu = &psxInt;
#endif
		if (psxCpu->Init() == -1) {
			SysClose(); return -1;
		}
		psxCpu->Reset();
	}

	return 0;
}

// remove the leading and trailing spaces in a string
void trim(char *str) {
	int pos = 0;
	char *dest = str;

	// skip leading blanks
	while (str[pos] <= ' ' && str[pos] > 0)
		pos++;

	while (str[pos]) {
		*(dest++) = str[pos];
		pos++;
	}

	*(dest--) = '\0'; // store the null

	// remove trailing blanks
	while (dest >= str && *dest <= ' ' && *dest > 0)
		*(dest--) = '\0';
}

// lookup table for crc calculation
static unsigned short crctab[256] = {
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7, 0x8108,
	0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF, 0x1231, 0x0210,
	0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6, 0x9339, 0x8318, 0xB37B,
	0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE, 0x2462, 0x3443, 0x0420, 0x1401,
	0x64E6, 0x74C7, 0x44A4, 0x5485, 0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE,
	0xF5CF, 0xC5AC, 0xD58D, 0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6,
	0x5695, 0x46B4, 0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D,
	0xC7BC, 0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
	0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B, 0x5AF5,
	0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12, 0xDBFD, 0xCBDC,
	0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A, 0x6CA6, 0x7C87, 0x4CE4,
	0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41, 0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD,
	0xAD2A, 0xBD0B, 0x8D68, 0x9D49, 0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13,
	0x2E32, 0x1E51, 0x0E70, 0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A,
	0x9F59, 0x8F78, 0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E,
	0xE16F, 0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
	0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E, 0x02B1,
	0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256, 0xB5EA, 0xA5CB,
	0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D, 0x34E2, 0x24C3, 0x14A0,
	0x0481, 0x7466, 0x6447, 0x5424, 0x4405, 0xA7DB, 0xB7FA, 0x8799, 0x97B8,
	0xE75F, 0xF77E, 0xC71D, 0xD73C, 0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657,
	0x7676, 0x4615, 0x5634, 0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9,
	0xB98A, 0xA9AB, 0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882,
	0x28A3, 0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
	0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92, 0xFD2E,
	0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9, 0x7C26, 0x6C07,
	0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1, 0xEF1F, 0xFF3E, 0xCF5D,
	0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8, 0x6E17, 0x7E36, 0x4E55, 0x5E74,
	0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

u16 calcCrc(u8 *d, int len) {
	u16 crc = 0;
	int i;

	for (i = 0; i < len; i++) {
		crc = crctab[(crc >> 8) ^ d[i]] ^ (crc << 8);
	}

	return ~crc;
}
