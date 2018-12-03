/*  Pcsx - Pc Psx Emulator
 *  Copyright (C) 1999-2002  Pcsx Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307 USA
 */

#ifndef __FRONTEND_MAIN_H__
#define __FRONTEND_MAIN_H__

#include "config.h"

#define DEFAULT_MEM_CARD_1 "/.pcsx/memcards/card1.mcd"
#define DEFAULT_MEM_CARD_2 "/.pcsx/memcards/card2.mcd"
#define MEMCARD_DIR "/.pcsx/memcards/"
#define PLUGINS_DIR "/.pcsx/plugins/"
#define PLUGINS_CFG_DIR "/.pcsx/plugins/cfg/"
#define PCSX_DOT_DIR "/.pcsx/"
#define STATES_DIR "/.pcsx/sstates/"
#define CHEATS_DIR "/.pcsx/cheats/"
#define PATCHES_DIR "/.pcsx/patches/"
#define BIOS_DIR "/bios/"
#define SCSHOT_DIR "/.pcsx/screenshots/"
#define LANG_IMG_DIR "/usr/sony/share/data/images/BMP_TXT_SST/"
#define DISK_IMG_DIR "/usr/sony/share/data/images/Disk/"

extern char cfgfile_basename[MAXPATHLEN];

#define POWER_DIR "/data/power/"
#define POWER_OFF_FILE "prepare_suspend"

#define CPU_TEMP_FILE "/dev/shm/power/cpu_temp"
#define CPU_TEMP_LIMIT_FILE "/dev/shm/power/temp_limit"
#define CPU_TEMP_LIMIT_STRING "CPU_AUTO_START_TEMP"
#define DEFAULT_TEMP_LIMIT 80000

#define DISPLAY_MODE_MIN 0
#define DISPLAY_MODE_MAX 1
#define DISPLAY_MODE_DEFAULT 1
#define LANGUAGE_MIN 1
#define LANGUAGE_MAX 13
#define LANGUAGE_DEFAULT 13
#define REGION_MIN 1
#define REGION_MAX 4
#define REGION_DEFAULT 3
#define ENTER_DEFAULT 0
extern int display_mode;
extern int language;
extern int region;

extern char changedisc_message[128];
extern char solodisc_message[128];
extern char nottime_message[128];
extern char ok_image[128];

extern int state_slot;

extern int from_escape;
extern int power_off_flg;
extern int is_high_temperature;
extern unsigned int memcardFlag;
extern unsigned int memcardFlagOld;
extern int memcardResetFlag;

/* emu_core_preinit - must be the very first call
 * emu_core_init - to be called after platform-specific setup */
int emu_core_preinit(void);
int emu_core_init(void);

void emu_core_ask_exit(void);

void emu_set_default_config(void);
void emu_on_new_cd(int show_hud_msg);

int get_state_filename(char *buf, int size, int i);
int emu_check_state(int slot);
int emu_save_state(int slot);
int emu_load_state(int slot);

void set_cd_image(const char *fname);

int create_power_off_thread(void);
void power_off(void);

extern unsigned long gpuDisp;
extern int ready_to_go, g_emu_want_quit, g_emu_resetting;

extern char hud_msg[64];
extern int hud_new_msg;

enum sched_action {
	SACTION_NONE,
	SACTION_ENTER_MENU,
	SACTION_LOAD_STATE,
	SACTION_SAVE_STATE,
	SACTION_NEXT_SSLOT,
	SACTION_PREV_SSLOT,
	SACTION_TOGGLE_FSKIP,
	SACTION_SWITCH_DISPMODE,
	SACTION_FAST_FORWARD,
	SACTION_SCREENSHOT,
	SACTION_VOLUME_UP,	// 10
	SACTION_VOLUME_DOWN,
	SACTION_MINIMIZE,
	SACTION_TOGGLE_FPS,
	SACTION_TOGGLE_FULLSCREEN,
	SACTION_GUN_TRIGGER = 16,
	SACTION_GUN_A,
	SACTION_GUN_B,
	SACTION_GUN_TRIGGER2,
	SACTION_RESET_EVENT,	// action when reset button pushed
	SACTION_POWER_OFF,      // action when power button pushed
	SACTION_CD_CHANGE,
	SACTION_SYNC_STATE,
};

#define SACTION_GUN_MASK (0x0f << SACTION_GUN_TRIGGER)

static inline void emu_set_action(enum sched_action action_)
{
	extern enum sched_action emu_action, emu_action_old;
	extern int stop;

	if (action_ == SACTION_NONE)
		emu_action_old = 0;
	else if (action_ != emu_action_old)
		stop = 1;
	emu_action = action_;
}

#endif /* __FRONTEND_MAIN_H__ */
