/*
 * (C) Gražvydas "notaz" Ignotas, 2012
 *
 * This work is licensed under the terms of any of these licenses
 * (at your option):
 *  - GNU GPL, version 2 or later.
 *  - GNU LGPL, version 2.1 or later.
 *  - MAME license.
 * See the COPYING file in the top-level directory.
 */

#include <stdio.h>
#include <SDL.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "input.h"
#include "in_sdl.h"
#if SDL_MAJOR_VERSION == 2
#include "keysym.h"
typedef int bool;
#define true 1
#define false 0
//#define CONFIG_DEBUG
#endif

#define IN_SDL_PREFIX "sdl:"
/* should be machine word for best performace */
typedef unsigned long keybits_t;
#define KEYBITS_WORD_BITS (sizeof(keybits_t) * 8)

struct in_sdl_state {
	const in_drv_t *drv;
	SDL_Joystick *joy;
	int joy_id;
	int axis_keydown[2];
	keybits_t keystate[SDLK_LAST / KEYBITS_WORD_BITS + 1];
};

static void (*ext_event_handler)(void *event);

#if SDL_MAJOR_VERSION == 2
SDLK_to_MY_SDLK SDLK_to_My_SDLK_ARRAY[] = {
  {SDLK_UNKNOWN,  MY_SDLK_UNKNOWN},

  {SDLK_RETURN, MY_SDLK_RETURN},
  {SDLK_ESCAPE, MY_SDLK_ESCAPE},
  {SDLK_BACKSPACE, MY_SDLK_BACKSPACE},
  {SDLK_TAB, MY_SDLK_TAB},
  {SDLK_SPACE, MY_SDLK_SPACE},
  {SDLK_EXCLAIM, MY_SDLK_EXCLAIM},
  {SDLK_QUOTEDBL, MY_SDLK_QUOTEDBL},
  {SDLK_HASH, MY_SDLK_HASH},
  {SDLK_PERCENT, MY_SDLK_PERCENT},
  {SDLK_DOLLAR, MY_SDLK_DOLLAR},
  {SDLK_AMPERSAND, MY_SDLK_AMPERSAND},
  {SDLK_QUOTE, MY_SDLK_QUOTE},
  {SDLK_LEFTPAREN, MY_SDLK_LEFTPAREN},
  {SDLK_RIGHTPAREN, MY_SDLK_RIGHTPAREN},
  {SDLK_ASTERISK, MY_SDLK_ASTERISK},
  {SDLK_PLUS, MY_SDLK_PLUS},
  {SDLK_COMMA, MY_SDLK_COMMA},
  {SDLK_MINUS, MY_SDLK_MINUS},
  {SDLK_PERIOD, MY_SDLK_PERIOD},
  {SDLK_SLASH, MY_SDLK_SLASH},
  {SDLK_0, MY_SDLK_0},
  {SDLK_1, MY_SDLK_1},
  {SDLK_2, MY_SDLK_2},
  {SDLK_3, MY_SDLK_3},
  {SDLK_4, MY_SDLK_4},
  {SDLK_5, MY_SDLK_5},
  {SDLK_6, MY_SDLK_6},
  {SDLK_7, MY_SDLK_7},
  {SDLK_8, MY_SDLK_8},
  {SDLK_9, MY_SDLK_9},
  {SDLK_COLON, MY_SDLK_COLON},
  {SDLK_SEMICOLON, MY_SDLK_SEMICOLON},
  {SDLK_LESS, MY_SDLK_LESS},
  {SDLK_EQUALS, MY_SDLK_EQUALS},
  {SDLK_GREATER, MY_SDLK_GREATER},
  {SDLK_QUESTION, MY_SDLK_QUESTION},
  {SDLK_AT, MY_SDLK_AT},
  /*
    Skip uppercase letters
  */
  {SDLK_LEFTBRACKET, MY_SDLK_LEFTBRACKET},
  {SDLK_BACKSLASH, MY_SDLK_BACKSLASH},
  {SDLK_RIGHTBRACKET, MY_SDLK_RIGHTBRACKET},
  {SDLK_CARET, MY_SDLK_CARET},
  {SDLK_UNDERSCORE, MY_SDLK_UNDERSCORE},
  {SDLK_BACKQUOTE, MY_SDLK_BACKQUOTE},
  {SDLK_a, MY_SDLK_a},
  {SDLK_b, MY_SDLK_b},
  {SDLK_c, MY_SDLK_c},
  {SDLK_d, MY_SDLK_d},
  {SDLK_e, MY_SDLK_e},
  {SDLK_f, MY_SDLK_f},
  {SDLK_g, MY_SDLK_g},
  {SDLK_h, MY_SDLK_h},
  {SDLK_i, MY_SDLK_i},
  {SDLK_j, MY_SDLK_j},
  {SDLK_k, MY_SDLK_k},
  {SDLK_l, MY_SDLK_l},
  {SDLK_m, MY_SDLK_m},
  {SDLK_n, MY_SDLK_n},
  {SDLK_o, MY_SDLK_o},
  {SDLK_p, MY_SDLK_p},
  {SDLK_q, MY_SDLK_q},
  {SDLK_r, MY_SDLK_r},
  {SDLK_s, MY_SDLK_s},
  {SDLK_t, MY_SDLK_t},
  {SDLK_u, MY_SDLK_u},
  {SDLK_v, MY_SDLK_v},
  {SDLK_w, MY_SDLK_w},
  {SDLK_x, MY_SDLK_x},
  {SDLK_y, MY_SDLK_y},
  {SDLK_z, MY_SDLK_z},

  {SDLK_CAPSLOCK, MY_SDLK_CAPSLOCK},

  {SDLK_F1, MY_SDLK_F1},
  {SDLK_F2, MY_SDLK_F2},
  {SDLK_F3, MY_SDLK_F3},
  {SDLK_F4, MY_SDLK_F4},
  {SDLK_F5, MY_SDLK_F5},
  {SDLK_F6, MY_SDLK_F6},
  {SDLK_F7, MY_SDLK_F7},
  {SDLK_F8, MY_SDLK_F8},
  {SDLK_F9, MY_SDLK_F9},
  {SDLK_F10, MY_SDLK_F10},
  {SDLK_F11, MY_SDLK_F11},
  {SDLK_F12, MY_SDLK_F12},

  {SDLK_PRINTSCREEN, MY_SDLK_PRINTSCREEN},
  {SDLK_SCROLLLOCK, MY_SDLK_SCROLLLOCK},
  {SDLK_PAUSE, MY_SDLK_PAUSE},
  {SDLK_INSERT, MY_SDLK_INSERT},
  {SDLK_HOME, MY_SDLK_HOME},
  {SDLK_PAGEUP, MY_SDLK_PAGEUP},
  {SDLK_DELETE, MY_SDLK_DELETE},
  {SDLK_END, MY_SDLK_END},
  {SDLK_PAGEDOWN, MY_SDLK_PAGEDOWN},
  {SDLK_RIGHT, MY_SDLK_RIGHT},
  {SDLK_LEFT, MY_SDLK_LEFT},
  {SDLK_DOWN, MY_SDLK_DOWN},
  {SDLK_UP, MY_SDLK_UP},

  {SDLK_NUMLOCKCLEAR, MY_SDLK_NUMLOCKCLEAR},
  {SDLK_KP_DIVIDE, MY_SDLK_KP_DIVIDE},
  {SDLK_KP_MULTIPLY, MY_SDLK_KP_MULTIPLY},
  {SDLK_KP_MINUS, MY_SDLK_KP_MINUS},
  {SDLK_KP_PLUS, MY_SDLK_KP_PLUS},
  {SDLK_KP_ENTER, MY_SDLK_KP_ENTER},
  {SDLK_KP_1, MY_SDLK_KP_1},
  {SDLK_KP_2, MY_SDLK_KP_2},
  {SDLK_KP_3, MY_SDLK_KP_3},
  {SDLK_KP_4, MY_SDLK_KP_4},
  {SDLK_KP_5, MY_SDLK_KP_5},
  {SDLK_KP_6, MY_SDLK_KP_6},
  {SDLK_KP_7, MY_SDLK_KP_7},
  {SDLK_KP_8, MY_SDLK_KP_8},
  {SDLK_KP_9, MY_SDLK_KP_9},
  {SDLK_KP_0, MY_SDLK_KP_0},
  {SDLK_KP_PERIOD, MY_SDLK_KP_PERIOD},

  {SDLK_APPLICATION, MY_SDLK_APPLICATION},
  {SDLK_POWER, MY_SDLK_POWER},
  {SDLK_KP_EQUALS, MY_SDLK_KP_EQUALS},
  {SDLK_F13, MY_SDLK_F13},
  {SDLK_F14, MY_SDLK_F14},
  {SDLK_F15, MY_SDLK_F15},
  {SDLK_F16, MY_SDLK_F16},
  {SDLK_F17, MY_SDLK_F17},
  {SDLK_F18, MY_SDLK_F18},
  {SDLK_F19, MY_SDLK_F19},
  {SDLK_F20, MY_SDLK_F20},
  {SDLK_F21, MY_SDLK_F21},
  {SDLK_F22, MY_SDLK_F22},
  {SDLK_F23, MY_SDLK_F23},
  {SDLK_F24, MY_SDLK_F24},
  {SDLK_EXECUTE, MY_SDLK_EXECUTE},
  {SDLK_HELP, MY_SDLK_HELP},
  {SDLK_MENU, MY_SDLK_MENU},
  {SDLK_SELECT, MY_SDLK_SELECT},
  {SDLK_STOP, MY_SDLK_STOP},
  {SDLK_AGAIN, MY_SDLK_AGAIN},
  {SDLK_UNDO, MY_SDLK_UNDO},
  {SDLK_CUT, MY_SDLK_CUT},
  {SDLK_COPY, MY_SDLK_COPY},
  {SDLK_PASTE, MY_SDLK_PASTE},
  {SDLK_FIND, MY_SDLK_FIND},
  {SDLK_MUTE, MY_SDLK_MUTE},
  {SDLK_VOLUMEUP, MY_SDLK_VOLUMEUP},
  {SDLK_VOLUMEDOWN, MY_SDLK_VOLUMEDOWN},
  {SDLK_KP_COMMA, MY_SDLK_KP_COMMA},
  {SDLK_KP_EQUALSAS400, MY_SDLK_KP_EQUALSAS400},

  {SDLK_ALTERASE, MY_SDLK_ALTERASE},
  {SDLK_SYSREQ, MY_SDLK_SYSREQ},
  {SDLK_CANCEL, MY_SDLK_CANCEL},
  {SDLK_CLEAR, MY_SDLK_CLEAR},
  {SDLK_PRIOR, MY_SDLK_PRIOR},
  {SDLK_RETURN2, MY_SDLK_RETURN2},
  {SDLK_SEPARATOR, MY_SDLK_SEPARATOR},
  {SDLK_OUT, MY_SDLK_OUT},
  {SDLK_OPER, MY_SDLK_OPER},
  {SDLK_CLEARAGAIN, MY_SDLK_CLEARAGAIN},
  {SDLK_CRSEL, MY_SDLK_CRSEL},
  {SDLK_EXSEL, MY_SDLK_EXSEL},

  {SDLK_KP_00, MY_SDLK_KP_00},
  {SDLK_KP_000, MY_SDLK_KP_000},
  {SDLK_THOUSANDSSEPARATOR, MY_SDLK_THOUSANDSSEPARATOR},
  {SDLK_DECIMALSEPARATOR, MY_SDLK_DECIMALSEPARATOR},
  {SDLK_CURRENCYUNIT, MY_SDLK_CURRENCYUNIT},
  {SDLK_CURRENCYSUBUNIT, MY_SDLK_CURRENCYSUBUNIT},
  {SDLK_KP_LEFTPAREN, MY_SDLK_KP_LEFTPAREN},
  {SDLK_KP_RIGHTPAREN, MY_SDLK_KP_RIGHTPAREN},
  {SDLK_KP_LEFTBRACE, MY_SDLK_KP_LEFTBRACE},
  {SDLK_KP_RIGHTBRACE, MY_SDLK_KP_RIGHTBRACE},
  {SDLK_KP_TAB, MY_SDLK_KP_TAB},
  {SDLK_KP_BACKSPACE, MY_SDLK_KP_BACKSPACE},
  {SDLK_KP_A, MY_SDLK_KP_A},
  {SDLK_KP_B, MY_SDLK_KP_B},
  {SDLK_KP_C, MY_SDLK_KP_C},
  {SDLK_KP_D, MY_SDLK_KP_D},
  {SDLK_KP_E, MY_SDLK_KP_E},
  {SDLK_KP_F, MY_SDLK_KP_F},
  {SDLK_KP_XOR, MY_SDLK_KP_XOR},
  {SDLK_KP_POWER, MY_SDLK_KP_POWER},
  {SDLK_KP_PERCENT, MY_SDLK_KP_PERCENT},
  {SDLK_KP_LESS, MY_SDLK_KP_LESS},
  {SDLK_KP_GREATER, MY_SDLK_KP_GREATER},
  {SDLK_KP_AMPERSAND, MY_SDLK_KP_AMPERSAND},
  {SDLK_KP_DBLAMPERSAND, MY_SDLK_KP_DBLAMPERSAND},
  {SDLK_KP_VERTICALBAR, MY_SDLK_KP_VERTICALBAR},
  {SDLK_KP_DBLVERTICALBAR, MY_SDLK_KP_DBLVERTICALBAR},
  {SDLK_KP_COLON, MY_SDLK_KP_COLON},
  {SDLK_KP_HASH, MY_SDLK_KP_HASH},
  {SDLK_KP_SPACE, MY_SDLK_KP_SPACE},
  {SDLK_KP_AT, MY_SDLK_KP_AT},
  {SDLK_KP_EXCLAM, MY_SDLK_KP_EXCLAM},
  {SDLK_KP_MEMSTORE, MY_SDLK_KP_MEMSTORE},
  {SDLK_KP_MEMRECALL, MY_SDLK_KP_MEMRECALL},
  {SDLK_KP_MEMCLEAR, MY_SDLK_KP_MEMCLEAR},
  {SDLK_KP_MEMADD, MY_SDLK_KP_MEMADD},
  {SDLK_KP_MEMSUBTRACT, MY_SDLK_KP_MEMSUBTRACT},
  {SDLK_KP_MEMMULTIPLY, MY_SDLK_KP_MEMMULTIPLY},
  {SDLK_KP_MEMDIVIDE, MY_SDLK_KP_MEMDIVIDE},
  {SDLK_KP_PLUSMINUS, MY_SDLK_KP_PLUSMINUS},
  {SDLK_KP_CLEAR, MY_SDLK_KP_CLEAR},
  {SDLK_KP_CLEARENTRY, MY_SDLK_KP_CLEARENTRY},
  {SDLK_KP_BINARY, MY_SDLK_KP_BINARY},
  {SDLK_KP_OCTAL, MY_SDLK_KP_OCTAL},
  {SDLK_KP_DECIMAL, MY_SDLK_KP_DECIMAL},
  {SDLK_KP_HEXADECIMAL, MY_SDLK_KP_HEXADECIMAL},

  {SDLK_LCTRL, MY_SDLK_LCTRL},
  {SDLK_LSHIFT, MY_SDLK_LSHIFT},
  {SDLK_LALT, MY_SDLK_LALT},
  {SDLK_LGUI, MY_SDLK_LGUI},
  {SDLK_RCTRL, MY_SDLK_RCTRL},
  {SDLK_RSHIFT, MY_SDLK_RSHIFT},
  {SDLK_RALT, MY_SDLK_RALT},
  {SDLK_RGUI, MY_SDLK_RGUI},

  {SDLK_MODE, MY_SDLK_MODE},

  {SDLK_AUDIONEXT, MY_SDLK_AUDIONEXT},
  {SDLK_AUDIOPREV, MY_SDLK_AUDIOPREV},
  {SDLK_AUDIOSTOP, MY_SDLK_AUDIOSTOP},
  {SDLK_AUDIOPLAY, MY_SDLK_AUDIOPLAY},
  {SDLK_AUDIOMUTE, MY_SDLK_AUDIOMUTE},
  {SDLK_MEDIASELECT, MY_SDLK_MEDIASELECT},
  {SDLK_WWW, MY_SDLK_WWW},
  {SDLK_MAIL, MY_SDLK_MAIL},
  {SDLK_CALCULATOR, MY_SDLK_CALCULATOR},
  {SDLK_COMPUTER, MY_SDLK_COMPUTER},
  {SDLK_AC_SEARCH, MY_SDLK_AC_SEARCH},
  {SDLK_AC_HOME, MY_SDLK_AC_HOME},
  {SDLK_AC_BACK, MY_SDLK_AC_BACK},
  {SDLK_AC_FORWARD, MY_SDLK_AC_FORWARD},
  {SDLK_AC_STOP, MY_SDLK_AC_STOP},
  {SDLK_AC_REFRESH, MY_SDLK_AC_REFRESH},
  {SDLK_AC_BOOKMARKS, MY_SDLK_AC_BOOKMARKS},

  {SDLK_BRIGHTNESSDOWN, MY_SDLK_BRIGHTNESSDOWN},
  {SDLK_BRIGHTNESSUP, MY_SDLK_BRIGHTNESSUP},
  {SDLK_DISPLAYSWITCH, MY_SDLK_DISPLAYSWITCH},
  {SDLK_KBDILLUMTOGGLE, MY_SDLK_KBDILLUMTOGGLE},
  {SDLK_KBDILLUMDOWN, MY_SDLK_KBDILLUMDOWN},
  {SDLK_KBDILLUMUP, MY_SDLK_KBDILLUMUP},
  {SDLK_EJECT, MY_SDLK_EJECT},
  {SDLK_SLEEP, MY_SDLK_SLEEP},
  //{SDLK_APP1, MY_SDLK_APP1},
  //{SDLK_APP2, MY_SDLK_APP2},

  //{SDLK_AUDIOREWIND, MY_SDLK_AUDIOREWIND},
  //{SDLK_AUDIOFASTFORWARD, MY_SDLK_AUDIOFASTFORWARD},

  {SDLK_LAST, MY_SDLK_UNKNOWN}
};    

static int func_SDLK_TO_MY_SDLK(int argSDLK) {
  int i = 0;
  
  do {
    if(SDLK_to_My_SDLK_ARRAY[i].m_SDLK == argSDLK) {
      break;
    }
    i++;
  } while(SDLK_to_My_SDLK_ARRAY[i].m_SDLK != SDLK_LAST);
  return SDLK_to_My_SDLK_ARRAY[i].m_MySDLK;
}

// SDL1で定義されているものを文字列と指定
static const char * const in_sdl_keys[SDLK_LAST] = {
        [MY_SDLK_BACKSPACE] = "backspace",
	[MY_SDLK_TAB] = "tab",
	[MY_SDLK_CLEAR] = "clear",
	[MY_SDLK_RETURN] = "return",
	[MY_SDLK_PAUSE] = "pause",
	[MY_SDLK_ESCAPE] = "escape",
	[MY_SDLK_SPACE] = "space",
	[MY_SDLK_EXCLAIM]  = "!",
	[MY_SDLK_QUOTEDBL]  = "\"",
	[MY_SDLK_HASH]  = "#",
	[MY_SDLK_DOLLAR]  = "$",
	[MY_SDLK_AMPERSAND]  = "&",
	[MY_SDLK_QUOTE] = "'",
	[MY_SDLK_LEFTPAREN] = "(",
	[MY_SDLK_RIGHTPAREN] = ")",
	[MY_SDLK_ASTERISK] = "*",
	[MY_SDLK_PLUS] = "+",
	[MY_SDLK_COMMA] = ",",
	[MY_SDLK_MINUS] = "-",
	[MY_SDLK_PERIOD] = ".",
	[MY_SDLK_SLASH] = "/",
	[MY_SDLK_0] = "0",
	[MY_SDLK_1] = "1",
	[MY_SDLK_2] = "2",
	[MY_SDLK_3] = "3",
	[MY_SDLK_4] = "4",
	[MY_SDLK_5] = "5",
	[MY_SDLK_6] = "6",
	[MY_SDLK_7] = "7",
	[MY_SDLK_8] = "8",
	[MY_SDLK_9] = "9",
	[MY_SDLK_COLON] = ":",
	[MY_SDLK_SEMICOLON] = ";",
	[MY_SDLK_LESS] = "<",
	[MY_SDLK_EQUALS] = "=",
	[MY_SDLK_GREATER] = ">",
	[MY_SDLK_QUESTION] = "?",
	[MY_SDLK_AT] = "@",
	[MY_SDLK_LEFTBRACKET] = "[",
	[MY_SDLK_BACKSLASH] = "\\",
	[MY_SDLK_RIGHTBRACKET] = "]",
	[MY_SDLK_CARET] = "^",
	[MY_SDLK_UNDERSCORE] = "_",
	[MY_SDLK_BACKQUOTE] = "`",
	[MY_SDLK_a] = "a",
	[MY_SDLK_b] = "b",
	[MY_SDLK_c] = "c",
	[MY_SDLK_d] = "d",
	[MY_SDLK_e] = "e",
	[MY_SDLK_f] = "f",
	[MY_SDLK_g] = "g",
	[MY_SDLK_h] = "h",
	[MY_SDLK_i] = "i",
	[MY_SDLK_j] = "j",
	[MY_SDLK_k] = "k",
	[MY_SDLK_l] = "l",
	[MY_SDLK_m] = "m",
	[MY_SDLK_n] = "n",
	[MY_SDLK_o] = "o",
	[MY_SDLK_p] = "p",
	[MY_SDLK_q] = "q",
	[MY_SDLK_r] = "r",
	[MY_SDLK_s] = "s",
	[MY_SDLK_t] = "t",
	[MY_SDLK_u] = "u",
	[MY_SDLK_v] = "v",
	[MY_SDLK_w] = "w",
	[MY_SDLK_x] = "x",
	[MY_SDLK_y] = "y",
	[MY_SDLK_z] = "z",
	[MY_SDLK_DELETE] = "delete",

	[MY_SDLK_KP_0] = "[0]",
	[MY_SDLK_KP_1] = "[1]",
	[MY_SDLK_KP_2] = "[2]",
	[MY_SDLK_KP_3] = "[3]",
	[MY_SDLK_KP_4] = "[4]",
	[MY_SDLK_KP_5] = "[5]",
	[MY_SDLK_KP_6] = "[6]",
	[MY_SDLK_KP_7] = "[7]",
	[MY_SDLK_KP_8] = "[8]",
	[MY_SDLK_KP_9] = "[9]",
	[MY_SDLK_KP_PERIOD] = "[.]",
	[MY_SDLK_KP_DIVIDE] = "[/]",
	[MY_SDLK_KP_MULTIPLY] = "[*]",
	[MY_SDLK_KP_MINUS] = "[-]",
	[MY_SDLK_KP_PLUS] = "[+]",
	[MY_SDLK_KP_ENTER] = "enter",
	[MY_SDLK_KP_EQUALS] = "equals",

	[MY_SDLK_UP] = "up",
	[MY_SDLK_DOWN] = "down",
	[MY_SDLK_RIGHT] = "right",
	[MY_SDLK_LEFT] = "left",
	[MY_SDLK_INSERT] = "insert",
	[MY_SDLK_HOME] = "home",
	[MY_SDLK_END] = "end",
	[MY_SDLK_PAGEUP] = "page up",
	[MY_SDLK_PAGEDOWN] = "page down",

	[MY_SDLK_F1] = "f1",
	[MY_SDLK_F2] = "f2",
	[MY_SDLK_F3] = "f3",
	[MY_SDLK_F4] = "f4",
	[MY_SDLK_F5] = "f5",
	[MY_SDLK_F6] = "f6",
	[MY_SDLK_F7] = "f7",
	[MY_SDLK_F8] = "f8",
	[MY_SDLK_F9] = "f9",
	[MY_SDLK_F10] = "f10",
	[MY_SDLK_F11] = "f11",
	[MY_SDLK_F12] = "f12",
	[MY_SDLK_F13] = "f13",
	[MY_SDLK_F14] = "f14",
	[MY_SDLK_F15] = "f15",

	[MY_SDLK_NUMLOCKCLEAR] = "numlock",
	[MY_SDLK_CAPSLOCK] = "caps lock",
	[MY_SDLK_SCROLLLOCK] = "scroll lock",
	[MY_SDLK_RSHIFT] = "right shift",
	[MY_SDLK_LSHIFT] = "left shift",
	[MY_SDLK_RCTRL] = "right ctrl",
	[MY_SDLK_LCTRL] = "left ctrl",
	[MY_SDLK_RALT] = "right alt",
	[MY_SDLK_LALT] = "left alt",
#ifdef NOTDEF
	[MY_SDLK_RMETA] = "right meta",
	[MY_SDLK_LMETA] = "left meta",
	[MY_SDLK_LSUPER] = "left super",	/* "Windows" keys */
	[MY_SDLK_RSUPER] = "right super",	
#endif
	[MY_SDLK_MODE] = "alt gr",
#ifdef NOTDEF
	[MY_SDLK_COMPOSE] = "compose",
#endif
	[MY_SDLK_EJECT] = "eject",
	[MY_SDLK_SLEEP] = "sleep",
	[MY_SDLK_AUDIOPLAY] = "reset",
};
#else
static const char * const in_sdl_keys[SDLK_LAST] = {
	[SDLK_BACKSPACE] = "backspace",
	[SDLK_TAB] = "tab",
	[SDLK_CLEAR] = "clear",
	[SDLK_RETURN] = "return",
	[SDLK_PAUSE] = "pause",
	[SDLK_ESCAPE] = "escape",
	[SDLK_SPACE] = "space",
	[SDLK_EXCLAIM]  = "!",
	[SDLK_QUOTEDBL]  = "\"",
	[SDLK_HASH]  = "#",
	[SDLK_DOLLAR]  = "$",
	[SDLK_AMPERSAND]  = "&",
	[SDLK_QUOTE] = "'",
	[SDLK_LEFTPAREN] = "(",
	[SDLK_RIGHTPAREN] = ")",
	[SDLK_ASTERISK] = "*",
	[SDLK_PLUS] = "+",
	[SDLK_COMMA] = ",",
	[SDLK_MINUS] = "-",
	[SDLK_PERIOD] = ".",
	[SDLK_SLASH] = "/",
	[SDLK_0] = "0",
	[SDLK_1] = "1",
	[SDLK_2] = "2",
	[SDLK_3] = "3",
	[SDLK_4] = "4",
	[SDLK_5] = "5",
	[SDLK_6] = "6",
	[SDLK_7] = "7",
	[SDLK_8] = "8",
	[SDLK_9] = "9",
	[SDLK_COLON] = ":",
	[SDLK_SEMICOLON] = ";",
	[SDLK_LESS] = "<",
	[SDLK_EQUALS] = "=",
	[SDLK_GREATER] = ">",
	[SDLK_QUESTION] = "?",
	[SDLK_AT] = "@",
	[SDLK_LEFTBRACKET] = "[",
	[SDLK_BACKSLASH] = "\\",
	[SDLK_RIGHTBRACKET] = "]",
	[SDLK_CARET] = "^",
	[SDLK_UNDERSCORE] = "_",
	[SDLK_BACKQUOTE] = "`",
	[SDLK_a] = "a",
	[SDLK_b] = "b",
	[SDLK_c] = "c",
	[SDLK_d] = "d",
	[SDLK_e] = "e",
	[SDLK_f] = "f",
	[SDLK_g] = "g",
	[SDLK_h] = "h",
	[SDLK_i] = "i",
	[SDLK_j] = "j",
	[SDLK_k] = "k",
	[SDLK_l] = "l",
	[SDLK_m] = "m",
	[SDLK_n] = "n",
	[SDLK_o] = "o",
	[SDLK_p] = "p",
	[SDLK_q] = "q",
	[SDLK_r] = "r",
	[SDLK_s] = "s",
	[SDLK_t] = "t",
	[SDLK_u] = "u",
	[SDLK_v] = "v",
	[SDLK_w] = "w",
	[SDLK_x] = "x",
	[SDLK_y] = "y",
	[SDLK_z] = "z",
	[SDLK_DELETE] = "delete",

	[SDLK_KP0] = "[0]",
	[SDLK_KP1] = "[1]",
	[SDLK_KP2] = "[2]",
	[SDLK_KP3] = "[3]",
	[SDLK_KP4] = "[4]",
	[SDLK_KP5] = "[5]",
	[SDLK_KP6] = "[6]",
	[SDLK_KP7] = "[7]",
	[SDLK_KP8] = "[8]",
	[SDLK_KP9] = "[9]",
	[SDLK_KP_PERIOD] = "[.]",
	[SDLK_KP_DIVIDE] = "[/]",
	[SDLK_KP_MULTIPLY] = "[*]",
	[SDLK_KP_MINUS] = "[-]",
	[SDLK_KP_PLUS] = "[+]",
	[SDLK_KP_ENTER] = "enter",
	[SDLK_KP_EQUALS] = "equals",

	[SDLK_UP] = "up",
	[SDLK_DOWN] = "down",
	[SDLK_RIGHT] = "right",
	[SDLK_LEFT] = "left",
	[SDLK_INSERT] = "insert",
	[SDLK_HOME] = "home",
	[SDLK_END] = "end",
	[SDLK_PAGEUP] = "page up",
	[SDLK_PAGEDOWN] = "page down",

	[SDLK_F1] = "f1",
	[SDLK_F2] = "f2",
	[SDLK_F3] = "f3",
	[SDLK_F4] = "f4",
	[SDLK_F5] = "f5",
	[SDLK_F6] = "f6",
	[SDLK_F7] = "f7",
	[SDLK_F8] = "f8",
	[SDLK_F9] = "f9",
	[SDLK_F10] = "f10",
	[SDLK_F11] = "f11",
	[SDLK_F12] = "f12",
	[SDLK_F13] = "f13",
	[SDLK_F14] = "f14",
	[SDLK_F15] = "f15",

	[SDLK_NUMLOCK] = "numlock",
	[SDLK_CAPSLOCK] = "caps lock",
	[SDLK_SCROLLOCK] = "scroll lock",
	[SDLK_RSHIFT] = "right shift",
	[SDLK_LSHIFT] = "left shift",
	[SDLK_RCTRL] = "right ctrl",
	[SDLK_LCTRL] = "left ctrl",
	[SDLK_RALT] = "right alt",
	[SDLK_LALT] = "left alt",
	[SDLK_RMETA] = "right meta",
	[SDLK_LMETA] = "left meta",
	[SDLK_LSUPER] = "left super",	/* "Windows" keys */
	[SDLK_RSUPER] = "right super",	
	[SDLK_MODE] = "alt gr",
	[SDLK_COMPOSE] = "compose",
	[SDLK_EJECT] = "eject",
	[SDLK_SLEEP] = "sleep",
	[SDLK_AUDIOPLAY] = "reset",
};
#endif

static void in_sdl_probe(const in_drv_t *drv)
{
	const struct in_pdata *pdata = drv->pdata;
	const char * const * key_names = in_sdl_keys;
	struct in_sdl_state *state;
	SDL_Joystick *joy;
	int i, joycount;
	char name[256];
	
	if (pdata->key_names)
		key_names = pdata->key_names;

	state = calloc(1, sizeof(*state));
	if (state == NULL) {
		fprintf(stderr, "in_sdl: OOM\n");
		return;
	}

	state->drv = drv;
	in_register(IN_SDL_PREFIX "keys", -1, state, SDLK_LAST,
		key_names, 0);

	/* joysticks go here too */
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	int fd0 = open("/dev/input/joystick0",O_RDONLY);
    int fd1 = open("/dev/input/joystick1",O_RDONLY);

	if( fd1 != -1 ){
		p2_connected = 1;
	}else{
		p2_connected = 0;
	}
	
	joycount = SDL_NumJoysticks();
	for (i = 0; i < joycount; i++) {
		joy = SDL_JoystickOpen(i);
		if (joy == NULL)
			continue;

		state = calloc(1, sizeof(*state));
		if (state == NULL) {
			fprintf(stderr, "in_sdl: OOM\n");
			break;
		}
		state->joy = joy;
		state->joy_id = i;
		state->drv = drv;

#if SDL_MAJOR_VERSION == 2

		if(fd1 != -1 && fd0 == -1) {
			snprintf(name, sizeof(name), IN_SDL_PREFIX "%s [%d]", SDL_JoystickName(joy), 1);
		} else {
			snprintf(name, sizeof(name), IN_SDL_PREFIX "%s", SDL_JoystickName(joy));
		}
		
#else
		snprintf(name, sizeof(name), IN_SDL_PREFIX "%s", SDL_JoystickName(i));
#endif
		in_register(name, -1, state, SDLK_LAST, key_names, 0);
	}

	if(fd0 != -1)
		close(fd0);
    if(fd1 != -1)
		close(fd1);

	if (joycount > 0)
		SDL_JoystickEventState(SDL_ENABLE);

}

static void in_sdl_free(void *drv_data)
{
	struct in_sdl_state *state = drv_data;

	if (state != NULL) {
		if (state->joy != NULL)
			SDL_JoystickClose(state->joy);
		free(state);
	}
}

static const char * const *
in_sdl_get_key_names(const in_drv_t *drv, int *count)
{
	const struct in_pdata *pdata = drv->pdata;
	*count = SDLK_LAST;

	if (pdata->key_names)
		return pdata->key_names;
	return in_sdl_keys;
}

/* could use SDL_GetKeyState, but this gives better packing */
static void update_keystate(keybits_t *keystate, int sym, int is_down)
{
        keybits_t *ks_word, mask;

	mask = 1;
	mask <<= sym & (KEYBITS_WORD_BITS - 1);
	ks_word = keystate + sym / KEYBITS_WORD_BITS;
	if (is_down)
		*ks_word |= mask;
	else
		*ks_word &= ~mask;
}

static int handle_event(struct in_sdl_state *state, SDL_Event *event,
	int *kc_out, int *down_out)
{
	if (event->type != SDL_KEYDOWN && event->type != SDL_KEYUP)
		return -1;

	update_keystate(state->keystate, event->key.keysym.sym,
		event->type == SDL_KEYDOWN);
	if (kc_out != NULL)
		*kc_out = event->key.keysym.sym;
	if (down_out != NULL)
		*down_out = event->type == SDL_KEYDOWN;

	return 1;
}

static int handle_joy_event(struct in_sdl_state *state, SDL_Event *event,
	int *kc_out, int *down_out)
{
	int kc = -1, down = 0, ret = 0;

	/* TODO: remaining axis */
	switch (event->type) {
	case SDL_JOYAXISMOTION:
#ifdef CONFIG_DEBUG
	  printf("%s:%d SDL_JOYAXISMOTION which=%d axis=%d value=%d\n",
		 __func__,
		 __LINE__,
		 event->jaxis.which,
		 event->jaxis.axis,
		 event->jaxis.value);
#endif
		if (event->jaxis.which != state->joy_id)
			return -2;
		if (event->jaxis.axis > 1)
			break;
		if (-16384 <= event->jaxis.value && event->jaxis.value <= 16384) {
			kc = state->axis_keydown[event->jaxis.axis];
			state->axis_keydown[event->jaxis.axis] = 0;
			ret = 1;
		}
		else if (event->jaxis.value < -16384) {
			kc = state->axis_keydown[event->jaxis.axis];
			if (kc)
				update_keystate(state->keystate, kc, 0);
#if SDL_MAJOR_VERSION == 2
			kc = event->jaxis.axis ? MY_SDLK_UP : MY_SDLK_LEFT;
#else
			kc = event->jaxis.axis ? SDLK_UP : SDLK_LEFT;
#endif
			state->axis_keydown[event->jaxis.axis] = kc;
			down = 1;
			ret = 1;
		}
		else if (event->jaxis.value > 16384) {
			kc = state->axis_keydown[event->jaxis.axis];
			if (kc)
				update_keystate(state->keystate, kc, 0);
#if SDL_MAJOR_VERSION == 2
			kc = event->jaxis.axis ? MY_SDLK_DOWN : MY_SDLK_RIGHT;
#else
			kc = event->jaxis.axis ? SDLK_DOWN : SDLK_RIGHT;
#endif
			state->axis_keydown[event->jaxis.axis] = kc;
			down = 1;
			ret = 1;
		}
		break;

	case SDL_JOYBUTTONDOWN:
	case SDL_JOYBUTTONUP:
#ifdef CONFIG_DEBUG
	  printf("%s:%d SDL_JOYBUTTONxxxx which=%d button=%d\n",
		 __func__,
		 __LINE__,
		 event->jbutton.which,
		 event->jbutton.button);
#endif
		if (event->jbutton.which != state->joy_id)
			return -2;
#if SDL_MAJOR_VERSION == 2
		kc = (int)event->jbutton.button + MY_SDLK_WORLD_0;
#else
		kc = (int)event->jbutton.button + SDLK_WORLD_0;
#endif
		down = event->jbutton.state == SDL_PRESSED;
		ret = 1;
		break;
	default:
#ifdef CONFIG_DEBUG
	  printf("%s:%d event=0x%x(%d)\n",
		 __func__,
		 __LINE__,
		 event->type,
		 event->type);
#endif
		return -1;
	}

	if (ret)
		update_keystate(state->keystate, kc, down);
	if (kc_out != NULL)
		*kc_out = kc;
	if (down_out != NULL)
		*down_out = down;

	return ret;
}

#if SDL_MAJOR_VERSION == 2
static void ControlJoysticEscape(struct in_sdl_state *arg_pState,
				 SDL_Event *arg_pEvent)
{
  SDL_Event myEvent;
  static bool bIsCurrentSelectButtonDown = false;
  static bool bIsCurrentStartButtonDown = false;

  bool bIsFormerSelectButtonDown = bIsCurrentSelectButtonDown;
  bool bIsFormerStartButtonDown = bIsCurrentStartButtonDown;
  char *env_menu, *endptr;
#ifdef CONFIG_ENABLE_MENU
  int env = 2;
#else
  int env = 0;
#endif
#ifdef CONFIG_DEBUG
       printf("%s:%d keysym.scancode=%d keysym.sym=%d keysym.mod=%d\n",
                                __func__,
                                __LINE__,
                                myEvent.key.keysym.scancode,
                                myEvent.key.keysym.sym,
                                myEvent.key.keysym.mod);
       printf("ControlJoysticEscape SDLK_WORLD %d",(arg_pEvent->jbutton.button + MY_SDLK_WORLD_0));

#endif

  if (arg_pState->joy) {
   env_menu = getenv("PCSX_ESC_KEY");
   if(env_menu != NULL) {
       env = strtol(env_menu, &endptr, 10);
       if(strlen(endptr) > 0 || env > 2) {
#ifdef CONFIG_ENABLE_MENU
         env = 2;
#else
         env = 0;
#endif
       }
   }

   switch(env) {
    case 0:
      break;
    case 1:
      if((arg_pEvent->jbutton.button + MY_SDLK_WORLD_0) == MY_SDLK_WORLD_8) {
        // "select" key event
        switch (arg_pEvent->type) {
        case SDL_JOYBUTTONDOWN:
          bIsCurrentSelectButtonDown = true;
	break;
        case SDL_JOYBUTTONUP:
          bIsCurrentSelectButtonDown = false;
	break;
      }

    } else if(((arg_pEvent->jbutton.button + MY_SDLK_WORLD_0) == MY_SDLK_WORLD_9)) {
      // "start" key event
      switch (arg_pEvent->type) {
      case SDL_JOYBUTTONDOWN:
	bIsCurrentStartButtonDown = true;
	break;
      case SDL_JOYBUTTONUP:
	bIsCurrentStartButtonDown = false;
	break;
      }
    }

    if(!((bIsFormerSelectButtonDown == true) && (bIsFormerStartButtonDown == true))
       &&
       ((bIsCurrentSelectButtonDown == true) && (bIsCurrentStartButtonDown == true))) {

        switch((arg_pEvent->jbutton.button + MY_SDLK_WORLD_0)) {
           case MY_SDLK_WORLD_9:
#ifdef CONFIG_DEBUG
               printf("ControlJoysticEscape SDL_SCANCODE_ESCAPE - SDL_KEYDOWN");
#endif
               myEvent.key.keysym.scancode = SDL_SCANCODE_ESCAPE;
               myEvent.key.keysym.sym = SDLK_ESCAPE;
               break;
        }

      // make ESC-key/Open-key/Reset-key down event
      myEvent.type = myEvent.key.type = SDL_KEYDOWN;
      myEvent.key.timestamp = arg_pEvent->key.timestamp;
      myEvent.key.windowID = 1;
      myEvent.key.state = 1;
      myEvent.key.repeat = 0;
      myEvent.key.keysym.mod = 0;

      SDL_PushEvent(&myEvent);

    } else if(((bIsFormerSelectButtonDown == true) && (bIsFormerStartButtonDown == true))
	      &&
	      !((bIsCurrentSelectButtonDown == true) && (bIsCurrentStartButtonDown == true))) {

      // make ESC-key up event
        switch((arg_pEvent->jbutton.button + MY_SDLK_WORLD_0)) {
           case MY_SDLK_WORLD_9:
#ifdef CONFIG_DEBUG
                printf("ControlJoysticEscape SDL_SCANCODE_ESCAPE - SDL_KEYUP");
#endif
               myEvent.key.keysym.scancode = SDL_SCANCODE_ESCAPE;
               myEvent.key.keysym.sym = SDLK_ESCAPE;
               break;
           case MY_SDLK_WORLD_0:
#ifdef CONFIG_DEBUG
                printf("ControlJoysticEscape SDL_SCANCODE_F9 - SDL_KEYUP");
#endif
               myEvent.key.keysym.scancode = SDL_SCANCODE_F9;
               myEvent.key.keysym.sym = SDLK_F9;
               break;
           case MY_SDLK_WORLD_1:
#ifdef CONFIG_DEBUG
                printf("ControlJoysticEscape SDL_SCANCODE_F10 - SDL_KEYUP");
#endif
               myEvent.key.keysym.scancode = SDL_SCANCODE_F10;
               myEvent.key.keysym.sym = SDLK_F10;
               break;
        }

      // make ESC-key/Open-key/Reset-key up event
      myEvent.type = myEvent.key.type = SDL_KEYUP;
      myEvent.key.timestamp = arg_pEvent->key.timestamp;
      myEvent.key.windowID = 1;
      myEvent.key.state = 0;
      myEvent.key.repeat = 0;
      myEvent.key.keysym.mod = 0;

      SDL_PushEvent(&myEvent);
    }
    break;
   case 2:
    if((arg_pEvent->jbutton.button + MY_SDLK_WORLD_0) == MY_SDLK_WORLD_8) {
      // "select" key event
      switch (arg_pEvent->type) {
      case SDL_JOYBUTTONDOWN:
        bIsCurrentSelectButtonDown = true;
        break;
      case SDL_JOYBUTTONUP:
        bIsCurrentSelectButtonDown = false;
        break;
      }

    } else if(((arg_pEvent->jbutton.button + MY_SDLK_WORLD_0) == MY_SDLK_WORLD_0)) {
      // "tryangle" key event
      switch (arg_pEvent->type) {
      case SDL_JOYBUTTONDOWN:
        bIsCurrentStartButtonDown = true;
        break;
      case SDL_JOYBUTTONUP:
        bIsCurrentStartButtonDown = false;
        break;
      }
    }

    if(!((bIsFormerSelectButtonDown == true) && (bIsFormerStartButtonDown == true))
       &&
       ((bIsCurrentSelectButtonDown == true) && (bIsCurrentStartButtonDown == true))) {
               myEvent.key.keysym.scancode = SDL_SCANCODE_ESCAPE;
               myEvent.key.keysym.sym = SDLK_ESCAPE;
	  myEvent.type = myEvent.key.type = SDL_KEYDOWN;
      myEvent.key.timestamp = arg_pEvent->key.timestamp;
      myEvent.key.windowID = 1;
      myEvent.key.state = 1;
      myEvent.key.repeat = 0;
      myEvent.key.keysym.mod = 0;

      SDL_PushEvent(&myEvent);

    } else if(((bIsFormerSelectButtonDown == true) && (bIsFormerStartButtonDown == true))
              &&
              !((bIsCurrentSelectButtonDown == true) && (bIsCurrentStartButtonDown == true))) {
               myEvent.key.keysym.scancode = SDL_SCANCODE_ESCAPE;
               myEvent.key.keysym.sym = SDLK_ESCAPE;

      // make ESC-key/Open-key/Reset-key up event
      myEvent.type = myEvent.key.type = SDL_KEYUP;
      myEvent.key.timestamp = arg_pEvent->key.timestamp;
      myEvent.key.windowID = 1;
      myEvent.key.state = 0;
      myEvent.key.repeat = 0;
      myEvent.key.keysym.mod = 0;

      SDL_PushEvent(&myEvent);
    }
   default:
    break;
   }
  }
}

#endif
#if SDL_MAJOR_VERSION == 1
#define JOY_EVENTS (SDL_JOYAXISMOTIONMASK | SDL_JOYBALLMOTIONMASK | SDL_JOYHATMOTIONMASK \
		    | SDL_JOYBUTTONDOWNMASK | SDL_JOYBUTTONUPMASK)
#endif

static int collect_events(struct in_sdl_state *state, int *one_kc, int *one_down)
{
	SDL_Event events[4];
#ifdef CONFIG_DEBUG
	static int cnt=0;
#endif
#if SDL_MAJOR_VERSION == 1
	Uint32 mask = state->joy ? JOY_EVENTS : (SDL_ALLEVENTS & ~JOY_EVENTS);
#else
	static int checkjoy0=0;
        int i=0, eventcnt=0;
	Uint32 minType;
	Uint32 maxType;
        eventcnt = SDL_PeepEvents(events,
                                  sizeof(events) / sizeof(events[0]),
                                  SDL_GETEVENT,
                                  SDL_JOYDEVICEADDED,
                                  SDL_JOYDEVICEREMOVED);
        if(eventcnt) {
#ifdef CONFIG_DEBUG
        	printf("eventcnt : %d\n", eventcnt);
        	printf("events->type : 0x%x\n", events->type);
        	printf("jdevice.which : %d\n", events->jdevice.which);
#endif
        	int check = 0;
		for(i=0; i < eventcnt; i++) {
                	check = bIsValidHotPlugEvent(&events[i]);
                    	if(check) {
                        	in_probe();
	        	}
	        }
		SDL_PumpEvents();
		SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
		fflush(stdout);
		if (check) {
			// SDL_JOYDEVICEADDED or SDL_JOYDEVICEREMOVED イベントあり
			// デバイス情報領域が再確保
			return -1;
		} else {
			for (i = 0; i < SDLK_LAST / KEYBITS_WORD_BITS + 1; i++) {
				if(state == NULL)
					break;
				state->keystate[i] = 0;
			}
			return 0;
		}
	}

#endif
	int count, maxcount;
	int ret, retval = 0;
	int num_events, num_peeped_events;
	SDL_Event *event;

	maxcount = (one_kc != NULL) ? 1 : sizeof(events) / sizeof(events[0]);

	SDL_PumpEvents();

#if SDL_MAJOR_VERSION == 2
	minType = SDL_KEYDOWN;
        maxType = SDL_KEYUP;
        if(state->joy) {
               minType = SDL_JOYAXISMOTION;
               maxType = SDL_JOYDEVICEREMOVED;
        }
	num_events = SDL_PeepEvents(NULL, 
				    0, 
				    SDL_PEEKEVENT, 
				    minType, 
				    maxType);
#ifdef CONFIG_DEBUG
	if(num_events) {
	  printf("%s:%d %d joy=%p num_events=%d\n",__func__,__LINE__,++cnt,state->joy,num_events);
	}
#endif
#else
	num_events = SDL_PeepEvents(NULL, 0, SDL_PEEKEVENT, mask);
#endif

	for (num_peeped_events = 0; num_peeped_events < num_events; num_peeped_events += count) {
#if SDL_MAJOR_VERSION == 2
	        count = SDL_PeepEvents(events, 
				       maxcount, 
				       SDL_GETEVENT, 
				       minType, 
				       maxType);
#else
		count = SDL_PeepEvents(events, maxcount, SDL_GETEVENT, mask);
#endif
		if (count <= 0)
			break;
		for (i = 0; i < count; i++) {
			event = &events[i];
#if SDL_MAJOR_VERSION == 2
			ControlJoysticEscape(state, event);

			if (state->joy)
				ret = handle_joy_event(state,
					event, one_kc, one_down);
			else {
#ifdef CONFIG_DEBUG
			  printf("%s:%d type=0x%x key.type=0x%x timestamp=%d windowID=%d state=%d repeat=%d keysym.scancode=%d keysym.sym=%d keysym.mod=%d\n",
				 __func__,
				 __LINE__,
				 event->type,
				 event->key.type,
				 event->key.timestamp,
				 event->key.windowID,
				 event->key.state,
				 event->key.repeat,
				 event->key.keysym.scancode,
				 event->key.keysym.sym,
				 event->key.keysym.mod);
#endif
			        event->key.keysym.sym = func_SDLK_TO_MY_SDLK(event->key.keysym.sym);
			        ret = handle_event(state,
					event, one_kc, one_down);
			}
#ifdef CONFIG_DEBUG
			if(one_kc) {
			  printf("%s:%d i=%d type(SDL_KEYDOWN or SDL_KEYUP)=0x%x timestamp=%d windowID=%d state(SDL_PRESSED or SDL_RELEASED)=%d repeat=%d one_key=0x%x(%d) scancode=0x%x(%d) sym=0x%x(%d) mod=%d\n" ,
				 __func__,
				 __LINE__,
				 i,
				 (event->key).type,            /* Uint32 */
				 (event->key).timestamp,       /* Uint32 */
				 (event->key).windowID,        /* Uint32 */
				 (event->key).state,           /* Uint8 */
				 (event->key).repeat,          /* Uint8 */
				 *one_kc,
				 *one_kc,
				 (event->key).keysym.scancode, /* enum */
				 (event->key).keysym.scancode, /* enum */
				 (event->key).keysym.sym,      /* int32 */
				 (event->key).keysym.sym,      /* int32 */
				 (event->key).keysym.mod);     /* Uint16 */
			} else {
			  printf("%s:%d i=%d type(SDL_KEYDOWN or SDL_KEYUP)=0x%x timestamp=%d windowID=%d state(SDL_PRESSED or SDL_RELEASED)=%d repeat=%d scancode=0x%x(%d) sym=0x%x(%d) mod=%d\n" ,
				 __func__,
				 __LINE__,
				 i,
				 (event->key).type,            /* Uint32 */
				 (event->key).timestamp,       /* Uint32 */
				 (event->key).windowID,        /* Uint32 */
				 (event->key).state,           /* Uint8 */
				 (event->key).repeat,          /* Uint8 */
				 (event->key).keysym.scancode, /* enum */
				 (event->key).keysym.scancode, /* enum */
				 (event->key).keysym.sym,      /* int32 */
				 (event->key).keysym.sym,      /* int32 */
				 (event->key).keysym.mod);     /* Uint16 */
			}
#endif // #ifdef CONFIG_DEBUG
#else // #if SDL_MAJOR_VERSION == 2
			if (state->joy)
				ret = handle_joy_event(state,
					event, one_kc, one_down);
			else
				ret = handle_event(state,
					event, one_kc, one_down);
#endif // #if SDL_MAJOR_VERSION == 2
			if (ret < 0) {
				switch (ret) {
					case -2:
						SDL_PushEvent(event);
						break;
					default:
						if (ext_event_handler != NULL)
							ext_event_handler(event);
						break;
				}
				continue;
			}

			retval |= ret;
			if (one_kc != NULL && ret)
			{
				// don't lose events other devices might want to handle
				for (i++; i < count; i++)
					SDL_PushEvent(&events[i]);
				goto out;
			}
		}
	}

out:
	return retval;
}

static int in_sdl_update(void *drv_data, const int *binds, int *result)
{
	struct in_sdl_state *state = drv_data;
	keybits_t mask;
	int i, sym, bit, b;

	if (collect_events(state, NULL, NULL) < 0)
		return 0;

	for (i = 0; i < SDLK_LAST / KEYBITS_WORD_BITS + 1; i++) {
		mask = state->keystate[i];
		if (mask == 0)
			continue;
		for (bit = 0; mask != 0; bit++, mask >>= 1) {
			if ((mask & 1) == 0)
				continue;
			sym = i * KEYBITS_WORD_BITS + bit;

			for (b = 0; b < IN_BINDTYPE_COUNT; b++)
				result[b] |= binds[IN_BIND_OFFS(sym, b)];
		}
	}

	return 0;
}

static int in_sdl_update_keycode(void *drv_data, int *is_down)
{
	struct in_sdl_state *state = drv_data;
	int ret_kc = -1, ret_down = 0;

	collect_events(state, &ret_kc, &ret_down);

	if (is_down != NULL)
		*is_down = ret_down;

	return ret_kc;
}

static int in_sdl_menu_translate(void *drv_data, int keycode, char *charcode)
{
	struct in_sdl_state *state = drv_data;
	const struct in_pdata *pdata = state->drv->pdata;
	const char * const * key_names = in_sdl_keys;
	const struct menu_keymap *map;
	int map_len;
	int ret = 0;
	int i;

	if (pdata->key_names)
		key_names = pdata->key_names;

	if (state->joy) {
		map = pdata->joy_map;
		map_len = pdata->jmap_size;
	} else {
		map = pdata->key_map;
		map_len = pdata->kmap_size;
	}

	if (keycode < 0)
	{
		/* menu -> kc */
		keycode = -keycode;
		for (i = 0; i < map_len; i++)
			if (map[i].pbtn == keycode)
				return map[i].key;
	}
	else
	{
		for (i = 0; i < map_len; i++) {
			if (map[i].key == keycode) {
				ret = map[i].pbtn;
				break;
			}
		}

		if (charcode != NULL && (unsigned int)keycode < SDLK_LAST &&
		    key_names[keycode] != NULL && key_names[keycode][1] == 0)
		{
			ret |= PBTN_CHAR;
			*charcode = key_names[keycode][0];
		}
	}

	return ret;
}

static const in_drv_t in_sdl_drv = {
	.prefix         = IN_SDL_PREFIX,
	.probe          = in_sdl_probe,
	.free           = in_sdl_free,
	.get_key_names  = in_sdl_get_key_names,
	.update         = in_sdl_update,
	.update_keycode = in_sdl_update_keycode,
	.menu_translate = in_sdl_menu_translate,
};

int in_sdl_init(const struct in_pdata *pdata, void (*handler)(void *event))
{
	if (!pdata) {
		fprintf(stderr, "in_sdl: Missing input platform data\n");
		return -1;
	}

	in_register_driver(&in_sdl_drv, pdata->defbinds, pdata);
	ext_event_handler = handler;
	return 0;
}
