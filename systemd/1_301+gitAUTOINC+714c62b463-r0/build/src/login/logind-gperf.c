/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf  */
/* Computed positions: -k'10' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif


#include <stddef.h>
#include "conf-parser.h"
#include "logind.h"
#include <string.h>

#define TOTAL_KEYWORDS 21
#define MIN_WORD_LENGTH 14
#define MAX_WORD_LENGTH 33
#define MIN_HASH_VALUE 14
#define MAX_HASH_VALUE 39
/* maximum key range = 26, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
logind_gperf_hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40,  0, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
       0,  0, 40, 40, 40, 15, 40, 40, 15, 40,
      40, 10,  0, 40,  0, 40,  0, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
      40, 40, 40, 40, 40, 40
    };
  return len + asso_values[(unsigned char)str[9]];
}

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct ConfigPerfItem *
logind_gperf_lookup (register const char *str, register unsigned int len)
{
  static const struct ConfigPerfItem wordlist[] =
    {
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
      {"Login.NAutoVTs",                    config_parse_unsigned,      0, offsetof(Manager, n_autovts)},
      {"Login.ReserveVT",                   config_parse_unsigned,      0, offsetof(Manager, reserve_vt)},
      {"Login.IdleAction",                  config_parse_handle_action, 0, offsetof(Manager, idle_action)},
      {(char*)0},
      {"Login.UserTasksMax",                config_parse_uint64,        0, offsetof(Manager, user_tasks_max)},
      {"Login.IdleActionSec",               config_parse_sec,           0, offsetof(Manager, idle_action_usec)},
      {"Login.HandlePowerKey",              config_parse_handle_action, 0, offsetof(Manager, handle_power_key)},
      {"Login.HandleLidSwitch",             config_parse_handle_action, 0, offsetof(Manager, handle_lid_switch)},
      {"Login.HandleSuspendKey",            config_parse_handle_action, 0, offsetof(Manager, handle_suspend_key)},
      {"Login.HoldoffTimeoutSec",           config_parse_sec,           0, offsetof(Manager, holdoff_timeout_usec)},
      {"Login.HandleHibernateKey",          config_parse_handle_action, 0, offsetof(Manager, handle_hibernate_key)},
      {"Login.RemoveIPC",                   config_parse_bool,          0, offsetof(Manager, remove_ipc)},
      {"Login.RuntimeDirectorySize",        config_parse_tmpfs_size,    0, offsetof(Manager, runtime_dir_size)},
      {"Login.HandleLidSwitchDocked",       config_parse_handle_action, 0, offsetof(Manager, handle_lid_switch_docked)},
      {(char*)0},
      {"Login.PowerKeyIgnoreInhibited",     config_parse_bool,          0, offsetof(Manager, power_key_ignore_inhibited)},
      {"Login.LidSwitchIgnoreInhibited",    config_parse_bool,          0, offsetof(Manager, lid_switch_ignore_inhibited)},
      {"Login.SuspendKeyIgnoreInhibited",   config_parse_bool,          0, offsetof(Manager, suspend_key_ignore_inhibited)},
      {(char*)0},
      {"Login.HibernateKeyIgnoreInhibited", config_parse_bool,          0, offsetof(Manager, hibernate_key_ignore_inhibited)},
      {"Login.KillOnlyUsers",               config_parse_strv,          0, offsetof(Manager, kill_only_users)},
      {(char*)0}, {(char*)0},
      {"Login.KillExcludeUsers",            config_parse_strv,          0, offsetof(Manager, kill_exclude_users)},
      {"Login.KillUserProcesses",           config_parse_bool,          0, offsetof(Manager, kill_user_processes)},
      {"Login.InhibitDelayMaxSec",          config_parse_sec,           0, offsetof(Manager, inhibit_delay_max)}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = logind_gperf_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].section_and_lvalue;

          if (s && *str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}
