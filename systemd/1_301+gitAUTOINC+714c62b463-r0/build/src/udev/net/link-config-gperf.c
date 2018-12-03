/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf  */
/* Computed positions: -k'7' */

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
#include "network-internal.h"
#include "link-config.h"
#include "ethtool-util.h"
#include <string.h>

#define TOTAL_KEYWORDS 19
#define MIN_WORD_LENGTH 9
#define MAX_WORD_LENGTH 23
#define MIN_HASH_VALUE 9
#define MAX_HASH_VALUE 40
/* maximum key range = 32, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
link_config_gperf_hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41,  5, 41, 41,  0, 41,
      41, 41, 30, 41, 41, 10, 41,  5, 41, 10,
      25, 41, 41, 41,  0, 41, 10, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41,  0, 41, 41,
      41,  0, 41, 41, 41,  0, 41, 41, 15, 41,
      41, 41, 41, 41, 41, 41, 41,  0, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
      41, 41, 41, 41, 41, 41
    };
  return len + asso_values[(unsigned char)str[6]];
}

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct ConfigPerfItem *
link_config_gperf_lookup (register const char *str, register unsigned int len)
{
  static const struct ConfigPerfItem wordlist[] =
    {
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
      {"Link.Name",                 config_parse_ifname,        0,                             offsetof(link_config, name)},
      {"Match.Type",                config_parse_strv,          0,                             offsetof(link_config, match_type)},
      {"Link.Duplex",               config_parse_duplex,        0,                             offsetof(link_config, duplex)},
      {"Match.Driver",              config_parse_strv,          0,                             offsetof(link_config, match_driver)},
      {"Link.MTUBytes",             config_parse_iec_size,      0,                             offsetof(link_config, mtu)},
      {"Link.WakeOnLan",            config_parse_wol,           0,                             offsetof(link_config, wol)},
      {"Link.NamePolicy",           config_parse_name_policy,   0,                             offsetof(link_config, name_policy)},
      {"Link.Description",          config_parse_string,        0,                             offsetof(link_config, description)},
      {(char*)0},
      {"Link.BitsPerSecond",        config_parse_si_size,       0,                             offsetof(link_config, speed)},
      {(char*)0},
      {"Link.MACAddress",           config_parse_hwaddr,        0,                             offsetof(link_config, mac)},
      {"Match.MACAddress",          config_parse_hwaddr,        0,                             offsetof(link_config, match_mac)},
      {(char*)0},
      {"Match.Architecture",        config_parse_net_condition, CONDITION_ARCHITECTURE,        offsetof(link_config, match_arch)},
      {(char*)0},
      {"Link.Alias",                config_parse_ifalias,       0,                             offsetof(link_config, alias)},
      {"Link.MACAddressPolicy",     config_parse_mac_policy,    0,                             offsetof(link_config, mac_policy)},
      {(char*)0},
      {"Match.OriginalName",        config_parse_ifnames,       0,                             offsetof(link_config, match_name)},
      {(char*)0},
      {"Match.Virtualization",      config_parse_net_condition, CONDITION_VIRTUALIZATION,      offsetof(link_config, match_virt)},
      {(char*)0}, {(char*)0},
      {"Match.KernelCommandLine",   config_parse_net_condition, CONDITION_KERNEL_COMMAND_LINE, offsetof(link_config, match_kernel)},
      {(char*)0},
      {"Match.Path",                config_parse_strv,          0,                             offsetof(link_config, match_path)},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"Match.Host",                config_parse_net_condition, CONDITION_HOST,                offsetof(link_config, match_host)}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = link_config_gperf_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].section_and_lvalue;

          if (s && *str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}
