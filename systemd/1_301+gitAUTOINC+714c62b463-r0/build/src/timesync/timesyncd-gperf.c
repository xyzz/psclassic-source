/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf  */
/* Computed positions: -k'' */


#include <stddef.h>
#include "conf-parser.h"
#include "timesyncd-conf.h"
#include <string.h>

#define TOTAL_KEYWORDS 3
#define MIN_WORD_LENGTH 8
#define MAX_WORD_LENGTH 16
#define MIN_HASH_VALUE 8
#define MAX_HASH_VALUE 16
/* maximum key range = 9, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
/*ARGSUSED*/
static unsigned int
timesyncdd_gperf_hash (register const char *str, register unsigned int len)
{
  return len;
}

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct ConfigPerfItem *
timesyncd_gperf_lookup (register const char *str, register unsigned int len)
{
  static const struct ConfigPerfItem wordlist[] =
    {
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"Time.NTP",           config_parse_servers, SERVER_SYSTEM,   0},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"Time.Servers",       config_parse_servers, SERVER_SYSTEM,   0},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"Time.FallbackNTP",   config_parse_servers, SERVER_FALLBACK, 0}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = timesyncdd_gperf_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].section_and_lvalue;

          if (s && *str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}
