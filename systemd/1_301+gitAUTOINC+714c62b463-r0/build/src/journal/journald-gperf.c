/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf  */
/* Computed positions: -k'9,18' */

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
#include <sys/socket.h>
#include "conf-parser.h"
#include "journald-server.h"
#include <string.h>

#define TOTAL_KEYWORDS 27
#define MIN_WORD_LENGTH 12
#define MAX_WORD_LENGTH 26
#define MIN_HASH_VALUE 12
#define MAX_HASH_VALUE 48
/* maximum key range = 37, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
journald_gperf_hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 10,  0, 49, 49,
       0, 49, 49, 15, 49, 20, 49,  0, 49, 49,
      49, 49,  5,  0, 25, 15, 49, 15, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 10, 49,  0,
      49, 20, 49, 49, 49, 20, 49, 49, 49, 49,
      49, 15, 10, 49, 49, 49,  0, 49, 10, 49,
       0,  5, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
      49, 49, 49, 49, 49, 49
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[17]];
      /*FALLTHROUGH*/
      case 17:
      case 16:
      case 15:
      case 14:
      case 13:
      case 12:
      case 11:
      case 10:
      case 9:
        hval += asso_values[(unsigned char)str[8]];
        break;
    }
  return hval;
}

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct ConfigPerfItem *
journald_gperf_lookup (register const char *str, register unsigned int len)
{
  static const struct ConfigPerfItem wordlist[] =
    {
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"Journal.Seal",               config_parse_bool,       0, offsetof(Server, seal)},
      {(char*)0}, {(char*)0},
      {"Journal.Storage",            config_parse_storage,    0, offsetof(Server, storage)},
      {"Journal.Compress",           config_parse_bool,       0, offsetof(Server, compress)},
      {"Journal.SplitMode",          config_parse_split_mode, 0, offsetof(Server, split_mode)},
      {"Journal.MaxFileSec",         config_parse_sec,        0, offsetof(Server, max_file_usec)},
      {(char*)0},
      {"Journal.MaxLevelKMsg",       config_parse_log_level,  0, offsetof(Server, max_level_kmsg)},
      {"Journal.MaxLevelStore",      config_parse_log_level,  0, offsetof(Server, max_level_store)},
      {"Journal.SystemMaxFiles",     config_parse_uint64,     0, offsetof(Server, system_metrics.n_max_files)},
      {"Journal.ForwardToSyslog",    config_parse_bool,       0, offsetof(Server, forward_to_syslog)},
      {"Journal.ForwardToConsole",   config_parse_bool,       0, offsetof(Server, forward_to_console)},
      {"Journal.SystemMaxFileSize",  config_parse_iec_uint64, 0, offsetof(Server, system_metrics.max_size)},
      {"Journal.RuntimeMaxUse",      config_parse_iec_uint64, 0, offsetof(Server, runtime_metrics.max_use)},
      {"Journal.MaxLevelSyslog",     config_parse_log_level,  0, offsetof(Server, max_level_syslog)},
      {"Journal.RuntimeMaxFiles",    config_parse_uint64,     0, offsetof(Server, runtime_metrics.n_max_files)},
      {(char*)0},
      {"Journal.MaxLevelWall",       config_parse_log_level,  0, offsetof(Server, max_level_wall)},
      {"Journal.RuntimeMaxFileSize", config_parse_iec_uint64, 0, offsetof(Server, runtime_metrics.max_size)},
      {"Journal.SystemKeepFree",     config_parse_iec_uint64, 0, offsetof(Server, system_metrics.keep_free)},
      {"Journal.SyncIntervalSec",    config_parse_sec,        0, offsetof(Server, sync_interval_usec)},
      {(char*)0},
      {"Journal.SystemMaxUse",       config_parse_iec_uint64, 0, offsetof(Server, system_metrics.max_use)},
      {"Journal.ForwardToWall",      config_parse_bool,       0, offsetof(Server, forward_to_wall)},
      {"Journal.RateLimitBurst",     config_parse_unsigned,   0, offsetof(Server, rate_limit_burst)},
      {"Journal.MaxLevelConsole",    config_parse_log_level,  0, offsetof(Server, max_level_console)},
      {(char*)0},
      {"Journal.TTYPath",            config_parse_path,       0, offsetof(Server, tty_path)},
      {"Journal.ForwardToKMsg",      config_parse_bool,       0, offsetof(Server, forward_to_kmsg)},
      {(char*)0},
      {"Journal.MaxRetentionSec",    config_parse_sec,        0, offsetof(Server, max_retention_usec)},
      {(char*)0},
      {"Journal.RateLimitInterval",  config_parse_sec,        0, offsetof(Server, rate_limit_interval)},
      {(char*)0}, {(char*)0},
      {"Journal.RuntimeKeepFree",    config_parse_iec_uint64, 0, offsetof(Server, runtime_metrics.keep_free)}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = journald_gperf_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].section_and_lvalue;

          if (s && *str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}
