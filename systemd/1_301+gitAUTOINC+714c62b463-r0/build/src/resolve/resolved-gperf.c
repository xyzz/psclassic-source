/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf  */
/* Computed positions: -k'' */


#include <stddef.h>
#include "conf-parser.h"
#include "resolved-conf.h"
#include <string.h>

#define TOTAL_KEYWORDS 5
#define MIN_WORD_LENGTH 11
#define MAX_WORD_LENGTH 19
#define MIN_HASH_VALUE 11
#define MAX_HASH_VALUE 19
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
resolved_gperf_hash (register const char *str, register unsigned int len)
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
resolved_gperf_lookup (register const char *str, register unsigned int len)
{
  static const struct ConfigPerfItem wordlist[] =
    {
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"Resolve.DNS",          config_parse_dns_servers,     DNS_SERVER_SYSTEM,   0},
      {(char*)0},
      {"Resolve.LLMNR",        config_parse_resolve_support, 0,                   offsetof(Manager, llmnr_support)},
      {"Resolve.DNSSEC",       config_parse_dnssec_mode,     0,                   offsetof(Manager, dnssec_mode)},
      {"Resolve.Domains",      config_parse_search_domains,  0,                   0},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"Resolve.FallbackDNS",  config_parse_dns_servers,     DNS_SERVER_FALLBACK, 0}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = resolved_gperf_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].section_and_lvalue;

          if (s && *str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}
