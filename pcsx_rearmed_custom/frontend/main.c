/*
 * (C) notaz, 2010-2012
 *
 * This work is licensed under the terms of the GNU GPLv2 or later.
 * See the COPYING file in the top-level directory.
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#ifndef _WIN32
#include <dlfcn.h>
#endif

#include "main.h"
#include "plugin.h"
#include "plugin_lib.h"
#include "pcnt.h"
#include "menu.h"
#include "plat.h"
#include "../libpcsxcore/misc.h"
#include "../libpcsxcore/cheat.h"
#include "../libpcsxcore/new_dynarec/new_dynarec.h"
#include "../plugins/cdrcimg/cdrcimg.h"
#include "../plugins/dfsound/spu_config.h"
#include "arm_features.h"
#include "revision.h"

#ifndef NO_FRONTEND
#include "libpicofe/input.h"
#include "libpicofe/plat.h"
#include "libpicofe/readpng.h"

static void toggle_fast_forward(int force_off);
static void check_profile(void);
static void check_memcards(void);
static int isOpenEnabled = 0;
#endif
#ifndef BOOT_MSG
#define BOOT_MSG "Booting up..."
#endif

#define EVENT_SIZE  (sizeof (struct inotify_event))
#define BUF_LEN     4096



// don't include debug.h - it breaks ARM build (R1 redefined)
void StartDebugger();
void StopDebugger();

int ready_to_go, g_emu_want_quit, g_emu_resetting;
unsigned long gpuDisp;
char cfgfile_basename[MAXPATHLEN];
int state_slot;
int from_escape = 0;
int power_off_flg = 0;
int is_high_temperature = 0;
enum sched_action emu_action, emu_action_old;
char hud_msg[64];
int hud_new_msg;
int isUnknowCdrom;
int holdResetEvent;

int display_mode = DISPLAY_MODE_DEFAULT;
int language = LANGUAGE_DEFAULT;
int region = REGION_DEFAULT;
int enter_mode = ENTER_DEFAULT;

static int cpu_temp_limit = DEFAULT_TEMP_LIMIT;

const char *lang_list[13] = {
	"German",		// de_de
	"E_UK",			// en_gb
	"E",			// en_us
	"Spanish_LA",		// es_419
	"Spanish",		// es_es
	"French_CA",		// fr_ca
	"French",		// fr_fr
	"Italian",		// it_it
	"Dutch",		// nl_nl
	"Portuguese_BR",	// pt_br
	"Portuguese",		// pt_pt
	"Russian",		// ru_ru
	"J"			// ja_jp
};

char changedisc_message[128];
char solodisc_message[128];
char nottime_message[128];
char ok_image[128];

static pthread_t th_power_off_state = (pthread_t)0;
static pthread_t cpu_temp_thread = (pthread_t)0;

static void make_path(char *buf, size_t size, const char *dir, const char *fname)
{
	if (fname)
		snprintf(buf, size, ".%s%s", dir, fname);
	else
		snprintf(buf, size, ".%s", dir);
}
#define MAKE_PATH(buf, dir, fname) \
	make_path(buf, sizeof(buf), dir, fname)

static int get_gameid_filename(char *buf, int size, const char *fmt, int i) {
	char trimlabel[33];
	int j;

	if (CdromLabel[0] != '\0' && !(g_opts & OPT_AUTOSAVE)) {
		strncpy(trimlabel, CdromLabel, 32);
	}
	else {
		strncpy(trimlabel, CdromLabel_old, 32);
	}
	trimlabel[32] = 0;
	for (j = 31; j >= 0; j--)
		if (trimlabel[j] == ' ')
			trimlabel[j] = 0;
		else
			continue;

	if (CdromId[0] != '\0' && !(g_opts & OPT_AUTOSAVE)) {
		snprintf(buf, size, fmt, trimlabel, CdromId, i);
	}
	else {
		snprintf(buf, size, fmt, trimlabel, CdromId_old, i);
	}

	return 0;
}

void set_cd_image(const char *fname)
{
	const char *ext = NULL;
	
	if (fname != NULL)
		ext = strrchr(fname, '.');

	if (ext && (
	    strcasecmp(ext, ".z") == 0 || strcasecmp(ext, ".bz") == 0 ||
	    strcasecmp(ext, ".znx") == 0 /*|| strcasecmp(ext, ".pbp") == 0*/)) {
		SetIsoFile(NULL);
		cdrcimg_set_fname(fname);
		strcpy(Config.Cdr, "builtin_cdrcimg");
	} else {
		SetIsoFile(fname);
		strcpy(Config.Cdr, "builtin_cdr");
	}
}

static void set_default_paths(void)
{
#ifndef NO_FRONTEND
	snprintf(Config.PatchesDir, sizeof(Config.PatchesDir), "." PATCHES_DIR);
	MAKE_PATH(Config.Mcd1, MEMCARD_DIR, "card1.mcd");
	MAKE_PATH(Config.Mcd2, MEMCARD_DIR, "none");
	strcpy(Config.BiosDir, "bios");
#endif

	strcpy(Config.PluginsDir, "plugins");
	strcpy(Config.Gpu, "builtin_gpu");
	strcpy(Config.Spu, "builtin_spu");
	strcpy(Config.Cdr, "builtin_cdr");
	strcpy(Config.Pad1, "builtin_pad");
	strcpy(Config.Pad2, "builtin_pad");
	strcpy(Config.Net, "Disabled");
}

void emu_set_default_config(void)
{
	// try to set sane config on which most games work
	Config.Xa = Config.Cdda = Config.Sio =
	Config.SpuIrq = Config.RCntFix = Config.VSyncWA = 0;
	Config.PsxAuto = 1;

	pl_rearmed_cbs.gpu_neon.allow_interlace = 2; // auto
	pl_rearmed_cbs.gpu_neon.enhancement_enable =
	pl_rearmed_cbs.gpu_neon.enhancement_no_main = 0;
	pl_rearmed_cbs.gpu_peops.iUseDither = 0;
	pl_rearmed_cbs.gpu_peops.dwActFixes = 1<<7;
	pl_rearmed_cbs.gpu_peops.isToShinDen = 0;
	pl_rearmed_cbs.gpu_peops.isBiosLogoEnd = 0;
	pl_rearmed_cbs.gpu_peops.scenes = 0;
	pl_rearmed_cbs.gpu_peops.regions = 0;
	pl_rearmed_cbs.gpu_unai.abe_hack =
	pl_rearmed_cbs.gpu_unai.no_light =
	pl_rearmed_cbs.gpu_unai.no_blend = 0;
	memset(&pl_rearmed_cbs.gpu_peopsgl, 0, sizeof(pl_rearmed_cbs.gpu_peopsgl));
	pl_rearmed_cbs.gpu_peopsgl.iVRamSize = 64;
	pl_rearmed_cbs.gpu_peopsgl.iTexGarbageCollection = 1;

	spu_config.iUseReverb = 1;
	spu_config.iUseInterpolation = 1;
	spu_config.iXAPitch = 0;
	spu_config.iVolume = 768;
	spu_config.iTempo = 0;
	spu_config.iUseThread = 1; // no effect if only 1 core is detected
#ifdef HAVE_PRE_ARMV7 /* XXX GPH hack */
	spu_config.iUseReverb = 0;
	spu_config.iUseInterpolation = 0;
	spu_config.iTempo = 1;
#endif
	new_dynarec_hacks = 0;
	cycle_multiplier = 200;

	in_type1 = PSE_PAD_TYPE_STANDARD;
	in_type2 = PSE_PAD_TYPE_STANDARD;
}

void do_emu_action(void)
{
	int ret;

	emu_action_old = emu_action;

	switch (emu_action) {
	case SACTION_LOAD_STATE:
		ret = emu_load_state(state_slot);
		snprintf(hud_msg, sizeof(hud_msg), ret == 0 ? "LOADED" : "FAIL!");
		break;
	case SACTION_SAVE_STATE:
		ret = emu_save_state(state_slot);
		snprintf(hud_msg, sizeof(hud_msg), ret == 0 ? "SAVED" : "FAIL!");
		break;
#ifndef NO_FRONTEND
	case SACTION_ENTER_MENU:
		from_escape = 1;
		toggle_fast_forward(1);
		menu_loop();
		return;
	case SACTION_NEXT_SSLOT:
		state_slot++;
		if (state_slot > 9)
			state_slot = 0;
		goto do_state_slot;
	case SACTION_PREV_SSLOT:
		state_slot--;
		if (state_slot < 0)
			state_slot = 9;
do_state_slot:
		snprintf(hud_msg, sizeof(hud_msg), "STATE SLOT %d [%s]", state_slot,
			emu_check_state(state_slot) == 0 ? "USED" : "FREE");
		hud_new_msg = 3;
		SysPrintf("* %s\n", hud_msg);
		break;
	case SACTION_TOGGLE_FSKIP:
		pl_rearmed_cbs.fskip_advice = 0;
		pl_rearmed_cbs.frameskip++;
		if (pl_rearmed_cbs.frameskip > 1)
			pl_rearmed_cbs.frameskip = -1;
		snprintf(hud_msg, sizeof(hud_msg), "FRAMESKIP: %s",
			pl_rearmed_cbs.frameskip == -1 ? "AUTO" :
			pl_rearmed_cbs.frameskip == 0 ? "OFF" : "1" );
		plugin_call_rearmed_cbs();
		break;
	case SACTION_SWITCH_DISPMODE:
		pl_switch_dispmode();
		plugin_call_rearmed_cbs();
		if (GPU_open != NULL && GPU_close != NULL) {
			GPU_close();
			GPU_open(&gpuDisp, "PCSX", NULL);
		}
		break;
	case SACTION_FAST_FORWARD:
		toggle_fast_forward(0);
		plugin_call_rearmed_cbs();
		break;
	case SACTION_TOGGLE_FPS:
		if ((g_opts & (OPT_SHOWFPS|OPT_SHOWCPU))
		    == (OPT_SHOWFPS|OPT_SHOWCPU))
			g_opts &= ~(OPT_SHOWFPS|OPT_SHOWCPU);
		else if (g_opts & OPT_SHOWFPS)
			g_opts |= OPT_SHOWCPU;
		else
			g_opts |= OPT_SHOWFPS;
		break;
	case SACTION_TOGGLE_FULLSCREEN:
		plat_target.vout_fullscreen = !plat_target.vout_fullscreen;
		if (GPU_open != NULL && GPU_close != NULL) {
			GPU_close();
			GPU_open(&gpuDisp, "PCSX", NULL);
		}
		break;
	case SACTION_SCREENSHOT:
		{
			char buf[MAXPATHLEN];
			void *scrbuf;
			int w, h, bpp;
			time_t t = time(NULL);
			struct tm *tb = localtime(&t);
			int ti = tb->tm_yday * 1000000 + tb->tm_hour * 10000 +
				tb->tm_min * 100 + tb->tm_sec;

			scrbuf = pl_prepare_screenshot(&w, &h, &bpp);
			get_gameid_filename(buf, sizeof(buf),
				"screenshots/%.32s-%.9s.%d.png", ti);
			ret = -1;
			if (scrbuf != 0 && bpp == 16)
				ret = writepng(buf, scrbuf, w, h);
			if (ret == 0)
				snprintf(hud_msg, sizeof(hud_msg), "SCREENSHOT TAKEN");
			break;
		}
	case SACTION_VOLUME_UP:
	case SACTION_VOLUME_DOWN:
		{
			static int volume;
			plat_target_step_volume(&volume,
				emu_action == SACTION_VOLUME_UP ? 1 : -1);
		}
		return;
	case SACTION_SYNC_STATE:
		emu_sync_state2();
		time_to_sync_state = 0;
		return;
	case SACTION_MINIMIZE:
		if (GPU_close != NULL)
			GPU_close();

		plat_minimize();

		if (GPU_open != NULL) {
			ret = GPU_open(&gpuDisp, "PCSX", NULL);
			if (ret)
				SysMessage("GPU_open returned %d", ret);
		}
		return;
#endif
	// add for open button
        case SACTION_CD_CHANGE:
                if (!isOpenEnabled) {
                        isOpenEnabled = CheckOpenEnabled();
                        if (!isOpenEnabled) {
                                return;
                        }
                }
                toggle_fast_forward(1);
                swap_cd();
                return;
        // add for power button
        case SACTION_POWER_OFF:
                power_off();
                return;
	// add for reset button
	case SACTION_RESET_EVENT:
		// save state of restart point
		// save state of restart point
		if (!(g_opts & OPT_AUTOSAVE) && isUnknownCdrom) {
			holdResetEvent = 1;
		}
		if ((memcardFlag==0)&&(memcardFlagOld==0)) {
		}
		else {
			memcardResetFlag = 1;
			return;
		}
		if (holdResetEvent) return;
		ret = emu_auto_save_state(0);
		snprintf(hud_msg, sizeof(hud_msg), ret == 0 ? "LOADED" : "FAIL!");
		if (ret) {
			char path[MAXPATHLEN];
			struct stat st;

			snprintf(path, sizeof(path), "." PCSX_DOT_DIR "filename.txt");
			ret = stat(path, &st);
			if (!ret) {
				remove(path);
			}
		}
		else {
			// screen picture
			char buf[MAXPATHLEN];
			void *scrbuf;
			int w, h, bpp;

			scrbuf = pl_prepare_screenshot(&w, &h, &bpp);
			get_gameid_filename(buf, sizeof(buf),
				"." SCSHOT_DIR "%.32s-%.9s.png", 0);
			ret = -1;
			if (scrbuf != 0 && bpp == 16)
				ret = writepng(buf, scrbuf, w, h);
			if (ret == 0)
				snprintf(hud_msg, sizeof(hud_msg), "SCREENSHOT TAKEN");

			// save file
			make_file_name();
		}
		// emulator exit
		stop = 1;
		g_emu_want_quit = 1;
	default:
		return;
	}

	hud_new_msg = 3;
}

static char basic_lcase(char c)
{
	if ('A' <= c && c <= 'Z')
		return c - 'A' + 'a';
	return c;
}

static int cdidcmp(const char *id1, const char *id2)
{
	while (*id1 != 0 && *id2 != 0) {
		if (*id1 == '_') { id1++; continue; }
		if (*id2 == '_') { id2++; continue; }
		if (basic_lcase(*id1) != basic_lcase(*id2))
			break;
		id1++;
		id2++;
	}

	return *id1 - *id2;
}

static void parse_cwcheat(void)
{
	char line[256], buf[64], name[64], *p;
	int newcheat = 1;
	u32 a, v;
	FILE *f;

	f = fopen("cheatpops.db", "r");
	if (f == NULL)
		return;

	/* find the game */
	while (fgets(line, sizeof(line), f)) {
		if (sscanf(line, "_S %63s", buf) != 1)
			continue;
		if (cdidcmp(buf, CdromId) == 0)
			break;
	}

	if (feof(f))
		goto out;

	SysPrintf("cwcheat section found for %s\n", CdromId);
	while (fgets(line, sizeof(line), f))
	{
		p = line + strlen(line);
		for (p--; p >= line && (*p == '\r' || *p == '\n' || *p == ' '); p--)
			*p = 0;
		if (*p == 0 || *p == '#' || *p == ';')
			continue;

		if (strncmp(line, "_S", 2) == 0)
			break;
		if (strncmp(line, "_G", 2) == 0) {
			SysPrintf("  cwcheat game name: '%s'\n", line + 3);
			continue;
		}
		if (strncmp(line, "_C0", 3) == 0) {
			if (!newcheat && Cheats[NumCheats - 1].n == 0) {
				SysPrintf("cheat '%s' failed to parse\n", name);
				free(Cheats[NumCheats - 1].Descr);
				NumCheats--;
			}
			snprintf(name, sizeof(name), "%s", line + 4);
			newcheat = 1;
			continue;
		}
		if (sscanf(line, "_L %x %x", &a, &v) != 2) {
			SysPrintf("line failed to parse: '%s'\n", line);
			continue;
		}

		if (newcheat) {
			if (NumCheats >= NumCheatsAllocated) {
				NumCheatsAllocated += 16;
				Cheats = realloc(Cheats, sizeof(Cheat) *
						NumCheatsAllocated);
				if (Cheats == NULL)
					break;
			}
			Cheats[NumCheats].Descr = strdup(name);
			Cheats[NumCheats].Enabled = 0;
			Cheats[NumCheats].WasEnabled = 0;
			Cheats[NumCheats].First = NumCodes;
			Cheats[NumCheats].n = 0;
			NumCheats++;
			newcheat = 0;
		}

		if (NumCodes >= NumCodesAllocated) {
			NumCodesAllocated += 16;
			CheatCodes = realloc(CheatCodes, sizeof(CheatCode) *
				NumCodesAllocated);
			if (CheatCodes == NULL)
				break;
		}
		CheatCodes[NumCodes].Addr = a;
		CheatCodes[NumCodes].Val = v;
		NumCodes++;
		Cheats[NumCheats - 1].n++;
	}

out:
	fclose(f);
}

void emu_on_new_cd(int show_hud_msg)
{
	ClearAllCheats();
	parse_cwcheat();

	if (Config.HLE) {
		SysPrintf("note: running with HLE BIOS, expect compatibility problems\n");
		SysPrintf("----------------------------------------------------------\n");
	}

	if (show_hud_msg) {
		//snprintf(hud_msg, sizeof(hud_msg), BOOT_MSG);
		hud_new_msg = 3;
	}
}

int emu_core_preinit(void)
{
	// what is the name of the config file?
	// it may be redefined by -cfg on the command line
	strcpy(cfgfile_basename, "pcsx.cfg");

#ifdef IOS
	emuLog = fopen("/User/Documents/pcsxr.log", "w");
	if (emuLog == NULL)
		emuLog = fopen("pcsxr.log", "w");
	if (emuLog == NULL)
#endif
	emuLog = stdout;

	SetIsoFile(NULL);

	memset(&Config, 0, sizeof(Config));

	set_default_paths();
	emu_set_default_config();
	strcpy(Config.Bios, "HLE");

	return 0;
}

int emu_core_init(void)
{
	SysPrintf("Starting PCSX-ReARMed " REV "\n");

#ifndef NO_FRONTEND
	check_profile();
	check_memcards();
#endif

	if (EmuInit() == -1) {
		SysPrintf("PSX emulator couldn't be initialized.\n");
		return -1;
	}

	LoadMcds(Config.Mcd1, Config.Mcd2);

	if (Config.Debug) {
		StartDebugger();
	}

	return 0;
}

void emu_core_ask_exit(void)
{
	stop = 1;
	g_emu_want_quit = 1;
}

#ifndef NO_FRONTEND

#include <sys/stat.h>
#include <sys/types.h>

static void create_profile_dir(const char *directory) {
	char path[MAXPATHLEN];

	MAKE_PATH(path, directory, NULL);
	mkdir(path, S_IRWXU | S_IRWXG);
}

static void check_profile(void) {
	// make sure that ~/.pcsx exists
	create_profile_dir(PCSX_DOT_DIR);

	create_profile_dir(BIOS_DIR);
	create_profile_dir(MEMCARD_DIR);
	create_profile_dir(STATES_DIR);
	create_profile_dir(PLUGINS_DIR);
	create_profile_dir(PLUGINS_CFG_DIR);
	create_profile_dir(CHEATS_DIR);
	create_profile_dir(PATCHES_DIR);
	create_profile_dir(PCSX_DOT_DIR "cfg");
//	create_profile_dir("/screenshots/");
	create_profile_dir(SCSHOT_DIR);
}

static void check_memcards(void)
{
	char buf[MAXPATHLEN];
	FILE *f;
	int i;

	for (i = 1; i <= 2; i++) {
		snprintf(buf, sizeof(buf), ".%scard%d.mcd", MEMCARD_DIR, i);

		f = fopen(buf, "rb");
		if (f == NULL) {
			SysPrintf("Creating memcard: %s\n", buf);
			CreateMcd(buf);
		}
		else
			fclose(f);
	}
}

static int check_prepare_suspend(void)
{
	char path[256];
	int ret = -1;
	FILE *f;
	snprintf(path, sizeof(path), POWER_DIR POWER_OFF_FILE);
	f = fopen(path, "rb");
	if (f == NULL) {
		ret = 0;
	}
	else {
		ret = -1;
		fclose(f);
	}
	return ret;
}

#ifdef UI_INTEGRATION
int main_ui(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	printf("+ frontend/main()\n");
	main_ui(argc,argv);
	printf("- frontend/main()\n");
}
int main_ui(int argc, char *argv[])
{
	printf("+ frontend/main_ui()\n");
#else
int main(int argc, char *argv[])
{
	//printf("+ frontend/main()\n");
#endif

	char file[MAXPATHLEN] = "";
	char path[MAXPATHLEN];
	const char *cdfile = NULL;
	const char *loadst_f = NULL;
	int psxout = 0;
	int loadst = 0;
	int i;
	int isGame = 0;

	emu_core_preinit();

	// read command line options
	for (i = 1; i < argc; i++) {
		     if (!strcmp(argv[i], "-psxout")) psxout = 1;
		else if (!strcmp(argv[i], "-load")) loadst = atol(argv[++i]);
		else if (!strcmp(argv[i], "-cfg")) {
			if (i+1 >= argc) break;
			strncpy(cfgfile_basename, argv[++i], MAXPATHLEN-100);	/* TODO buffer overruns */
			SysPrintf("Using config file %s.\n", cfgfile_basename);
		}
		else if (!strcmp(argv[i], "-cdfile")) {
			printf("argv[i]=%s\n",argv[i]);
			printf("argv[i+1]=%s\n",argv[i+1]);
			char isofilename[MAXPATHLEN];

			if (i+1 >= argc) break;
			strncpy(isofilename, argv[++i], MAXPATHLEN);
			if (isofilename[0] != '/') {
				getcwd(path, MAXPATHLEN);
				if (strlen(path) + strlen(isofilename) + 1 < MAXPATHLEN) {
					strcat(path, "/");
					strcat(path, isofilename);
					strcpy(isofilename, path);
				} else
					isofilename[0] = 0;
			}

			cdfile = isofilename;
		}
		else if (!strcmp(argv[i], "-loadf")) {
			if (i+1 >= argc) break;
			loadst_f = argv[++i];
		}
		else if (!strcmp(argv[i], "-display")) {
			if (i+1 >= argc) {
				break;
			}
			display_mode = atoi(argv[++i]);
			if (DISPLAY_MODE_MIN > display_mode || DISPLAY_MODE_MAX < display_mode) {
				display_mode = DISPLAY_MODE_DEFAULT;
			}
		}
		else if (!strcmp(argv[i], "-lang")) {
			if (i+1 >= argc) {
				break;
			}
			language = atoi(argv[++i]);
			if (LANGUAGE_MIN > language || LANGUAGE_MAX < language) {
				language = LANGUAGE_DEFAULT;
			}
		}
		else if (!strcmp(argv[i], "-region")) {
			if (i+1 >= argc) {
				break;
			}
			region = atoi(argv[++i]);
			if (REGION_MIN > region || REGION_MAX < region) {
				region = REGION_DEFAULT;
			}
		}
		else if (!strcmp(argv[i], "-enter")) {
			if (i+1 >= argc) {
				break;
			}
			enter_mode = atoi(argv[++i]);
		}
		else if (!strcmp(argv[i], "-h") ||
			 !strcmp(argv[i], "-help") ||
			 !strcmp(argv[i], "--help")) {
			 printf("PCSX-ReARMed " REV "\n");
			 printf("%s\n", _(
							" pcsx [options] [file]\n"
							"\toptions:\n"
							"\t-cdfile FILE\tRuns a CD image file\n"
							"\t-cfg FILE\tLoads desired configuration file (default: ~/.pcsx/pcsx.cfg)\n"
							"\t-psxout\t\tEnable PSX output\n"
							"\t-load STATENUM\tLoads savestate STATENUM (1-5)\n"
							"\t-h -help\tDisplay this message\n"
							"\tfile\t\tLoads a PSX EXE file\n"));
			 return 0;
		}
		else if (!strcmp(argv[i], "-v") ||
			!strcmp(argv[i], "--version")) {
				printf(REV "\n");
				return 0;
		} else {
			strncpy(file, argv[i], MAXPATHLEN);
			if (file[0] != '/') {
				getcwd(path, MAXPATHLEN);
				if (strlen(path) + strlen(file) + 1 < MAXPATHLEN) {
					strcat(path, "/");
					strcat(path, file);
					strcpy(file, path);
				} else
					file[0] = 0;
			}
		}
	}
	sprintf(changedisc_message, "%s%s%s%s", LANG_IMG_DIR, "msg_current_inserted_disc_info_", lang_list[language-1], ".png");
	sprintf(solodisc_message, "%s%s%s%s", LANG_IMG_DIR, "msg_cant_change_discs_this_game_", lang_list[language-1], ".png");
	sprintf(nottime_message, "%s%s%s%s", LANG_IMG_DIR, "msg_cant_change_discs_now_", lang_list[language-1], ".png");
	sprintf(ok_image, "%s%s%s%s", DISK_IMG_DIR, "OK_SD_Btn_", lang_list[language-1], ".png");

	if (cdfile) {
		printf("set_cd_image(cdfile)\n");
		set_cd_image(cdfile);
	}

	// frontend stuff
	// init input but leave probing to platform code,
	// they add input drivers and may need to modify them after probe
	in_init();
	pl_init();
        if (cdfile != NULL) {
		isGame = 1;
        }
	plat_init(isGame, enter_mode);
	setTitleName();
	menu_init(); // loads config

	if (emu_core_init() != 0)
		return 1;

	if (psxout)
		Config.PsxOut = 1;

	if (LoadPlugins() == -1) {
		// FIXME: this recovery doesn't work, just delete bad config and bail out
		// SysMessage("could not load plugins, retrying with defaults\n");
		set_default_paths();
		snprintf(path, sizeof(path), "." PCSX_DOT_DIR "%s", cfgfile_basename);
		remove(path);
		SysMessage("Failed loading plugins!");
		return 1;
	}
	pcnt_hook_plugins();

	if (OpenPlugins() == -1) {
		return 1;
	}
	plugin_call_rearmed_cbs();

	CheckCdrom();
	// save file
	make_file_name();
	save_error(ERROR_PCSXCRITICALERROR, "Sorry, error occurred during running system...");
	SysReset();

	if (file[0] != '\0') {
		if (Load(file) != -1)
			ready_to_go = 1;
	} else {
		if (cdfile) {
			if (LoadCdrom() == -1) {
				ClosePlugins();
				SysPrintf(_("Could not load CD-ROM!\n"));
				return -1;
			}
			emu_on_new_cd(!loadst);
			ready_to_go = 1;
		}
	}

	if (loadst_f) {
		int ret = LoadState(loadst_f);
		SysPrintf("%s state file: %s\n",
			ret ? "failed to load" : "loaded", loadst_f);
		ready_to_go |= ret == 0;
	}

	if (ready_to_go) {
		menu_prepare_emu();

		// If a state has been specified, then load that
		if (loadst) {
			int ret = emu_load_state(loadst - 1);
			SysPrintf("%s state %d\n",
				ret ? "failed to load" : "loaded", loadst);
		}
	}
	else
		menu_loop();

	pl_start_watchdog();
        // create thread for watching communication file
        if (create_power_off_thread() != 0) {
               printf("failed to create power off thread\n");
               return -1;
        }
        if (check_prepare_suspend() != 0) {
               power_off();
        }
        // create thread for watching cpu temperature
        if (begin_watch_cpu_temperature() != 0) {
               printf("failed to create thread for watching cpu temperature\n");
               return -1;
        }

	StartCheckOpen();

	printf("while (g_emu_want_quit=%d) start \n",g_emu_want_quit);
	while (!g_emu_want_quit)
	{
		stop = 0;
		emu_action = SACTION_NONE;

		psxCpu->Execute();
#ifdef UI_INTEGRATION
		g_emu_want_quit = -1;
#else
		if (emu_action != SACTION_NONE) {
			do_emu_action();
		}
#endif
	}
	printf("while (g_emu_want_quit=%d) end \n",g_emu_want_quit);

	printf("Exit..\n");
	ClosePlugins();
	SysClose();
	menu_finish();
	plat_finish();

	unlink(STATUS_DIR"001.sts");
	
	printf("- plat_sdl/main.c:main()\n");
	return 0;
}

static void toggle_fast_forward(int force_off)
{
	static int fast_forward;
	static int normal_g_opts;
	static int normal_frameskip;
	static int normal_enhancement_enable;

	if (force_off && !fast_forward)
		return;

	fast_forward = !fast_forward;
	if (fast_forward) {
		normal_g_opts = g_opts;
		normal_frameskip = pl_rearmed_cbs.frameskip;
		normal_enhancement_enable =
			pl_rearmed_cbs.gpu_neon.enhancement_enable;

		g_opts |= OPT_NO_FRAMELIM;
		pl_rearmed_cbs.frameskip = 3;
		pl_rearmed_cbs.gpu_neon.enhancement_enable = 0;
	} else {
		g_opts = normal_g_opts;
		pl_rearmed_cbs.frameskip = normal_frameskip;
		pl_rearmed_cbs.gpu_neon.enhancement_enable =
			normal_enhancement_enable;

		pl_timing_prepare(Config.PsxType);
	}

	if (!force_off)
		snprintf(hud_msg, sizeof(hud_msg), "FAST FORWARD %s",
			fast_forward ? "ON" : "OFF");
}

static void SignalExit(int sig) {
	// only to restore framebuffer/resolution on some devices
	plat_finish();
	exit(1);
}
#endif

void SysRunGui() {
        printf("SysRunGui\n");
}

static void dummy_lace()
{
}

void SysReset() {
	// rearmed hack: EmuReset() runs some code when real BIOS is used,
	// but we usually do reset from menu while GPU is not open yet,
	// so we need to prevent updateLace() call..
	void *real_lace = GPU_updateLace;
	GPU_updateLace = dummy_lace;
	g_emu_resetting = 1;

	// reset can run code, timing must be set
	pl_timing_prepare(Config.PsxType);

	EmuReset();

	// hmh core forgets this
	CDR_stop();

	GPU_updateLace = real_lace;
	g_emu_resetting = 0;
}

void SysClose() {
	EmuShutdown();
	ReleasePlugins();

	StopDebugger();

	if (emuLog != NULL && emuLog != stdout && emuLog != stderr) {
		fclose(emuLog);
		emuLog = NULL;
	}
}

void SysUpdate() {
}

int get_state_filename(char *buf, int size, int i) {
	return get_gameid_filename(buf, size,
		"." STATES_DIR "%.32s-%.9s.%3.3d", i);
}

int emu_check_state(int slot)
{
	char fname[MAXPATHLEN];
	int ret;

	ret = get_state_filename(fname, sizeof(fname), slot);
	if (ret != 0)
		return ret;

	return CheckState(fname);
}

int emu_auto_save_state(int slot)
{
	char fname[MAXPATHLEN];
	int ret;

	ret = get_state_filename(fname, sizeof(fname), slot);
	if (ret != 0)
		return ret;

	ret = SaveStateWork(fname);
#ifdef HAVE_PRE_ARMV7 /* XXX GPH hack */
	sync();
#endif
	SysPrintf("* %s \"%s\" [%d]\n",
		ret == 0 ? "saved" : "failed to save", fname, slot);
	return ret;
}

int emu_save_state(int slot)
{
	char fname[MAXPATHLEN];
	int ret;

	ret = get_state_filename(fname, sizeof(fname), slot);
	if (ret != 0)
		return ret;

	ret = SaveState(fname);
#ifdef HAVE_PRE_ARMV7 /* XXX GPH hack */
	sync();
#endif
	SysPrintf("* %s \"%s\" [%d]\n",
		ret == 0 ? "saved" : "failed to save", fname, slot);
	return ret;
}

int emu_load_state(int slot)
{
	char fname[MAXPATHLEN];
	int ret;

	hud_msg[0] = 0;

	ret = get_state_filename(fname, sizeof(fname), slot);
	if (ret != 0)
		return ret;

	return LoadState(fname);
}

#ifndef ANDROID

void SysPrintf(const char *fmt, ...) {
	va_list list;

	va_start(list, fmt);
	vfprintf(emuLog, fmt, list);
	va_end(list);
	fflush(emuLog);
}

#else

#include <android/log.h>

void SysPrintf(const char *fmt, ...) {
	va_list list;

	va_start(list, fmt);
	__android_log_vprint(ANDROID_LOG_INFO, "PCSX", fmt, list);
	va_end(list);
}

#endif

void SysMessage(const char *fmt, ...) {
	va_list list;
	char msg[512];
	int ret;

	va_start(list, fmt);
	ret = vsnprintf(msg, sizeof(msg), fmt, list);
	va_end(list);

	if (ret < sizeof(msg) && msg[ret - 1] == '\n')
		msg[ret - 1] = 0;

	SysPrintf("%s\n", msg);
}

#define PARSEPATH(dst, src) \
	ptr = src + strlen(src); \
	while (*ptr != '\\' && ptr != src) ptr--; \
	if (ptr != src) { \
		strcpy(dst, ptr+1); \
	}

static int _OpenPlugins(void) {
	int ret;

#ifndef NO_FRONTEND
	signal(SIGINT, SignalExit);
	signal(SIGPIPE, SignalExit);
#endif

	GPU_clearDynarec(clearDynarec);

	ret = CDR_open();
	if (ret < 0) { SysMessage(_("Error opening CD-ROM plugin!")); return -1; }
	ret = SPU_open();
	if (ret < 0) { SysMessage(_("Error opening SPU plugin!")); return -1; }
	SPU_registerCallback(SPUirq);
	SPU_registerScheduleCb(SPUschedule);
	// pcsx-rearmed: we handle gpu elsewhere
	//ret = GPU_open(&gpuDisp, "PCSX", NULL);
	//if (ret < 0) { SysMessage(_("Error opening GPU plugin!")); return -1; }
	ret = PAD1_open(&gpuDisp);
	if (ret < 0) { SysMessage(_("Error opening Controller 1 plugin!")); return -1; }
	ret = PAD2_open(&gpuDisp);
	if (ret < 0) { SysMessage(_("Error opening Controller 2 plugin!")); return -1; }

	if (Config.UseNet && !NetOpened) {
		netInfo info;
		char path[MAXPATHLEN];
		char dotdir[MAXPATHLEN];

		MAKE_PATH(dotdir, "/.pcsx/plugins/", NULL);

		strcpy(info.EmuName, "PCSX");
		strncpy(info.CdromID, CdromId, 9);
		strncpy(info.CdromLabel, CdromLabel, 9);
		info.psxMem = psxM;
		info.GPU_showScreenPic = GPU_showScreenPic;
		info.GPU_displayText = GPU_displayText;
		info.GPU_showScreenPic = GPU_showScreenPic;
		info.PAD_setSensitive = PAD1_setSensitive;
		sprintf(path, "%s%s", Config.BiosDir, Config.Bios);
		strcpy(info.BIOSpath, path);
		strcpy(info.MCD1path, Config.Mcd1);
		strcpy(info.MCD2path, Config.Mcd2);
		sprintf(path, "%s%s", dotdir, Config.Gpu);
		strcpy(info.GPUpath, path);
		sprintf(path, "%s%s", dotdir, Config.Spu);
		strcpy(info.SPUpath, path);
		sprintf(path, "%s%s", dotdir, Config.Cdr);
		strcpy(info.CDRpath, path);
		NET_setInfo(&info);

		ret = NET_open(&gpuDisp);
		if (ret < 0) {
			if (ret == -2) {
				// -2 is returned when something in the info
				// changed and needs to be synced
				char *ptr;

				PARSEPATH(Config.Bios, info.BIOSpath);
				PARSEPATH(Config.Gpu,  info.GPUpath);
				PARSEPATH(Config.Spu,  info.SPUpath);
				PARSEPATH(Config.Cdr,  info.CDRpath);

				strcpy(Config.Mcd1, info.MCD1path);
				strcpy(Config.Mcd2, info.MCD2path);
				return -2;
			} else {
				Config.UseNet = FALSE;
			}
		} else {
			if (NET_queryPlayer() == 1) {
				if (SendPcsxInfo() == -1) Config.UseNet = FALSE;
			} else {
				if (RecvPcsxInfo() == -1) Config.UseNet = FALSE;
			}
		}
		NetOpened = TRUE;
	} else if (Config.UseNet) {
		NET_resume();
	}

	return 0;
}

int OpenPlugins() {
	int ret;

	while ((ret = _OpenPlugins()) == -2) {
		ReleasePlugins();
		LoadMcds(Config.Mcd1, Config.Mcd2);
		if (LoadPlugins() == -1) return -1;
	}
	return ret;
}

void ClosePlugins() {
	int ret;

#ifndef NO_FRONTEND
	signal(SIGINT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
#endif

	ret = CDR_close();
	if (ret < 0) { SysMessage(_("Error closing CD-ROM plugin!")); return; }
	ret = SPU_close();
	if (ret < 0) { SysMessage(_("Error closing SPU plugin!")); return; }
	ret = PAD1_close();
	if (ret < 0) { SysMessage(_("Error closing Controller 1 Plugin!")); return; }
	ret = PAD2_close();
	if (ret < 0) { SysMessage(_("Error closing Controller 2 plugin!")); return; }
	// pcsx-rearmed: we handle gpu elsewhere
	//ret = GPU_close();
	//if (ret < 0) { SysMessage(_("Error closing GPU plugin!")); return; }

	if (Config.UseNet) {
		NET_pause();
	}
}

/* we hook statically linked plugins here */
static const char *builtin_plugins[] = {
	"builtin_gpu", "builtin_spu", "builtin_cdr", "builtin_pad",
	"builtin_cdrcimg",
};

static const int builtin_plugin_ids[] = {
	PLUGIN_GPU, PLUGIN_SPU, PLUGIN_CDR, PLUGIN_PAD,
	PLUGIN_CDRCIMG,
};

void *SysLoadLibrary(const char *lib) {
	const char *tmp = strrchr(lib, '/');
	void *ret = NULL;
	int i;

	SysPrintf("plugin: %s\n", lib);

	if (tmp != NULL) {
		tmp++;
		for (i = 0; i < ARRAY_SIZE(builtin_plugins); i++)
			if (strcmp(tmp, builtin_plugins[i]) == 0)
				return (void *)(long)(PLUGIN_DL_BASE + builtin_plugin_ids[i]);
	}

#ifndef _WIN32
	ret = dlopen(lib, RTLD_NOW);
	if (ret == NULL)
		SysMessage("dlopen: %s", dlerror());
#else
	/* no external plugin support, abi is no longer
	 * compatible with psemu/pcsx anyway */
#endif
	return ret;
}

void *SysLoadSym(void *lib, const char *sym) {
	unsigned int plugid = (unsigned int)(long)lib;

	if (PLUGIN_DL_BASE <= plugid && plugid < PLUGIN_DL_BASE + ARRAY_SIZE(builtin_plugins))
		return plugin_link(plugid - PLUGIN_DL_BASE, sym);

#ifndef _WIN32
	return dlsym(lib, sym);
#else
	return NULL;
#endif
}

const char *SysLibError() {
#ifndef _WIN32
	return dlerror();
#else
	return "not supported";
#endif
}

void SysCloseLibrary(void *lib) {
	unsigned int plugid = (unsigned int)(long)lib;

	if (PLUGIN_DL_BASE <= plugid && plugid < PLUGIN_DL_BASE + ARRAY_SIZE(builtin_plugins))
		return;

#ifndef _WIN32
	dlclose(lib);
#endif
}

static int check_poweroff_event(int power_fd) {
	int i = 0;
	char buffer[BUF_LEN];
	int event_length = 0;
	char file_name[sizeof(POWER_OFF_FILE)] = POWER_OFF_FILE;

	event_length = read(power_fd, buffer, BUF_LEN);
	if(event_length <= 0) {
		return 1;
	}
	while (i < event_length) {
		struct inotify_event* event = (struct inotify_event *) &buffer[i];
		if (strcmp(file_name, event->name) == 0) {
			 return 0;
		}
		i += EVENT_SIZE + event->len;
	}
	return 1;
}

static void power_manage(void) {
	int power_fd = -1;
	int power_wd = -1;
	int is_power_on = 1;

	power_fd = inotify_init();
	if(power_fd == -1) {
		printf("ERROR:failed to init inotify for power manage\n");
		return;
	}

	power_wd = inotify_add_watch(power_fd, POWER_DIR, IN_CREATE);
	if(power_wd == -1) {
		printf("ERROR:failed to add watch descriptor for power manage\n");
		return;
	}

	while (is_power_on) {
		is_power_on = check_poweroff_event(power_fd);
	}

	inotify_rm_watch(power_fd, power_wd);
	close(power_fd);

	power_off_flg = 1;

	return;
}

int create_power_off_thread(void) {
	int ret;
	pthread_attr_t power_manage_attr;

	if (th_power_off_state > 0) {
		printf("auto power off thread is already started, id [%d] \n", th_power_off_state);
		return -1;
	}
	pthread_attr_init(&power_manage_attr);
	pthread_attr_setdetachstate(&power_manage_attr , PTHREAD_CREATE_DETACHED);

	ret = pthread_create(&th_power_off_state, &power_manage_attr, (void*)power_manage, NULL);
	pthread_attr_destroy(&power_manage_attr);

	return ret;
}

void power_off(void)
{
        char path[MAXPATHLEN];
        struct stat st;

        snprintf(path, sizeof(path), "." PCSX_DOT_DIR "filename.txt");
        if(stat(path, &st) == 0) {
		remove(path);
        }

	// terminate pcsx
        stop = 1;
        g_emu_want_quit = 1;
}

// sub-thread for watching cpu temperature
static int check_cpu_temperature(int cpu_temp_fd)
{
	int cpu_temperature, cpu_mode;
	FILE *fp;
	char buffer[BUF_LEN];
	int ret;

	int is_normal_temp = 1;
	int event_length = 0;

	event_length = read(cpu_temp_fd, buffer, BUF_LEN);
	if(event_length <= 0) {
		return 0;
	}
	fp = fopen(CPU_TEMP_FILE, "r");
	ret = fscanf(fp, "%d%d", &cpu_temperature, &cpu_mode);
	if (ret != EOF) {
		is_normal_temp = (cpu_temperature < cpu_temp_limit) ? 1 : 0;
	}
	fclose(fp);
	return is_normal_temp;
}

static void watch_cpu_temperature(void)
{
	int cpu_temp_fd;
	int cpu_temp_wd;
	char temp_limit_str[strlen(CPU_TEMP_LIMIT_STRING)+1];
	int temp_limit_val;
	int ret;
	FILE *fp;

	cpu_temp_fd = inotify_init();
	if (cpu_temp_fd == -1) {
		printf("ERROR:failed to init inotify for cpu temperature\n");
	}

	cpu_temp_wd = inotify_add_watch(cpu_temp_fd, CPU_TEMP_FILE, IN_MODIFY);
	if (cpu_temp_wd == -1) {
		printf("ERROR:failed to add watch descriptor for cpu temperature\n");
	}

	fp = fopen(CPU_TEMP_LIMIT_FILE, "r");
	if (fp != NULL) {
		do {
			ret = fscanf(fp, "%s%d", &temp_limit_str, &temp_limit_val);
			if (strcmp(temp_limit_str, CPU_TEMP_LIMIT_STRING) == 0) {
				cpu_temp_limit = temp_limit_val;
				break;
			}
		} while (ret != EOF);
	}
	fclose(fp);

	while (1) {
		ret = check_cpu_temperature(cpu_temp_fd);
		if (ret == 0) {
			break;
		}
	}

	inotify_rm_watch(cpu_temp_fd, cpu_temp_wd);
	close(cpu_temp_fd);

	is_high_temperature = 1;
}

int begin_watch_cpu_temperature(void)
{
        int ret;
        pthread_attr_t cpu_temp_attr;

        pthread_attr_init(&cpu_temp_attr);
        pthread_attr_setdetachstate(&cpu_temp_attr , PTHREAD_CREATE_DETACHED);

        ret = pthread_create(&cpu_temp_thread, &cpu_temp_attr, watch_cpu_temperature, NULL);
        pthread_attr_destroy(&cpu_temp_attr);

        return ret;
}
