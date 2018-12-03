/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf  */
/* Computed positions: -k'6,9' */

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
#include "nspawn-settings.h"
#include "nspawn-expose-ports.h"
#include <string.h>

#define TOTAL_KEYWORDS 24
#define MIN_WORD_LENGTH 9
#define MAX_WORD_LENGTH 28
#define MIN_HASH_VALUE 9
#define MAX_HASH_VALUE 45
/* maximum key range = 37, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
nspawn_gperf_hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46,  0, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 10, 25, 15,  5,
      46, 46, 46,  0, 46,  5, 46, 15, 46, 46,
       0, 46, 46, 46, 46,  0,  0,  0, 46, 46,
      46, 46, 46, 46, 46, 46, 46,  5, 46, 20,
      46, 46, 46, 46, 10,  5, 46,  0, 20,  0,
       0, 46, 10, 46,  0,  0, 10, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
      46, 46, 46, 46, 46, 46
    };
  return len + asso_values[(unsigned char)str[8]] + asso_values[(unsigned char)str[5]];
}

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct ConfigPerfItem *
nspawn_gperf_lookup (register const char *str, register unsigned int len)
{
  static const struct ConfigPerfItem wordlist[] =
    {
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
      {"Exec.User",                    config_parse_string,        0, offsetof(Settings, user)},
      {"Files.Bind",                   config_parse_bind,          0, 0},
      {(char*)0},
      {"Network.Port",                 config_parse_expose_port,   0, 0},
      {(char*)0},
      {"Network.IPVLAN",               config_parse_strv,          0, offsetof(Settings, network_ipvlan)},
      {"Network.Private",              config_parse_tristate,      0, offsetof(Settings, private_network)},
      {"Exec.Personality",             config_parse_personality,   0, offsetof(Settings, personality)},
      {"Network.Interface",            config_parse_strv,          0, offsetof(Settings, network_interfaces)},
      {"Files.BindReadOnly",           config_parse_bind,          1, 0},
      {"Files.ReadOnly",               config_parse_tristate,      0, offsetof(Settings, read_only)},
      {"Exec.Parameters",              config_parse_strv,          0, offsetof(Settings, parameters)},
      {"Exec.WorkingDirectory",        config_parse_path,          0, offsetof(Settings, working_directory)},
      {(char*)0},
      {"Network.VirtualEthernet",      config_parse_tristate,      0, offsetof(Settings, network_veth)},
      {"Network.Bridge",               config_parse_string,        0, offsetof(Settings, network_bridge)},
      {"Files.TemporaryFileSystem",    config_parse_tmpfs,         0, 0},
      {"Exec.Environment",             config_parse_strv,          0, offsetof(Settings, environment)},
      {(char*)0},
      {"Network.VirtualEthernetExtra", config_parse_veth_extra,    0, 0},
      {"Exec.Boot",                    config_parse_boot,          0, 0},
      {"Network.MACVLAN",              config_parse_strv,          0, offsetof(Settings, network_macvlan)},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"Files.Volatile",               config_parse_volatile_mode, 0, offsetof(Settings, volatile_mode)},
      {"Exec.ProcessTwo",              config_parse_pid2,          0, 0,},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"Exec.MachineID",               config_parse_id128,         0, offsetof(Settings, machine_id)},
      {"Exec.KillSignal",              config_parse_signal,        0, offsetof(Settings, kill_signal)},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"Exec.DropCapability",          config_parse_capability,    0, offsetof(Settings, drop_capability)},
      {"Exec.Capability",              config_parse_capability,    0, offsetof(Settings, capability)}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = nspawn_gperf_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].section_and_lvalue;

          if (s && *str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}
