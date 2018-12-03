/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf -L ANSI-C -t --ignore-case -N lookup_arphrd -H hash_arphrd_name -p -C  */
/* Computed positions: -k'2-3,$' */

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

struct arphrd_name { const char* name; int id; };

#define TOTAL_KEYWORDS 58
#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 18
#define MIN_HASH_VALUE 5
#define MAX_HASH_VALUE 135
/* maximum key range = 131, duplicates = 0 */

#ifndef GPERF_DOWNCASE
#define GPERF_DOWNCASE 1
static unsigned char gperf_downcase[256] =
  {
      0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,
     15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,
     30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,
     45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
     60,  61,  62,  63,  64,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106,
    107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
    122,  91,  92,  93,  94,  95,  96,  97,  98,  99, 100, 101, 102, 103, 104,
    105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
    120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134,
    135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
    150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164,
    165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
    180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194,
    195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209,
    210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224,
    225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
    240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254,
    255
  };
#endif

#ifndef GPERF_CASE_STRCMP
#define GPERF_CASE_STRCMP 1
static int
gperf_case_strcmp (register const char *s1, register const char *s2)
{
  for (;;)
    {
      unsigned char c1 = gperf_downcase[(unsigned char)*s1++];
      unsigned char c2 = gperf_downcase[(unsigned char)*s2++];
      if (c1 != 0 && c1 == c2)
        continue;
      return (int)c1 - (int)c2;
    }
}
#endif

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash_arphrd_name (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136, 136, 136, 136, 136,  55,
        0,   0,  60,   0,  15, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136,  20,  55,  15,   5,   5,
       10,   0,  60,   0,  45,  25,  10,  25,  45,  15,
        0,  25,   0,  15,   0,   5, 136,  25,   5,   5,
      136, 136, 136, 136, 136, 136, 136,  20,  55,  15,
        5,   5,  10,   0,  60,   0,  45,  25,  10,  25,
       45,  15,   0,  25,   0,  15,   0,   5, 136,  25,
        5,   5, 136, 136, 136, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136, 136, 136, 136, 136, 136,
      136, 136, 136, 136, 136, 136, 136
    };
  return len + asso_values[(unsigned char)str[2]+1] + asso_values[(unsigned char)str[1]] + asso_values[(unsigned char)str[len - 1]];
}

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct arphrd_name *
lookup_arphrd (register const char *str, register unsigned int len)
{
  static const struct arphrd_name wordlist[] =
    {
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
      {"ETHER", ARPHRD_ETHER},
      {"PRONET", ARPHRD_PRONET},
      {(char*)0},
      {"SIT", ARPHRD_SIT},
      {"AX25", ARPHRD_AX25},
      {"IPDDP", ARPHRD_IPDDP},
      {"ARCNET", ARPHRD_ARCNET},
      {(char*)0},
      {"BIF", ARPHRD_BIF},
      {"FDDI", ARPHRD_FDDI},
      {"DDCMP", ARPHRD_DDCMP},
      {"EETHER", ARPHRD_EETHER},
      {(char*)0},
      {"X25", ARPHRD_X25},
      {"DLCI", ARPHRD_DLCI},
      {"CISCO", ARPHRD_CISCO},
      {"ECONET", ARPHRD_ECONET},
      {"IEEE802", ARPHRD_IEEE802},
      {(char*)0},
      {"ROSE", ARPHRD_ROSE},
      {"IEEE802_TR", ARPHRD_IEEE802_TR},
      {(char*)0}, {(char*)0},
      {"PPP", ARPHRD_PPP},
      {"IRDA", ARPHRD_IRDA},
      {"HIPPI", ARPHRD_HIPPI},
      {(char*)0}, {(char*)0},
      {"IEEE80211_RADIOTAP", ARPHRD_IEEE80211_RADIOTAP},
      {"IEEE802154_PHY", ARPHRD_IEEE802154_PHY},
      {"HWX25", ARPHRD_HWX25},
      {"TUNNEL", ARPHRD_TUNNEL},
      {(char*)0},
      {"FCFABRIC", ARPHRD_FCFABRIC},
      {"NONE", ARPHRD_NONE},
      {"RSRVD", ARPHRD_RSRVD},
      {"NETROM", ARPHRD_NETROM},
      {"TUNNEL6", ARPHRD_TUNNEL6},
      {"METRICOM", ARPHRD_METRICOM},
      {"FCPP", ARPHRD_FCPP},
      {"CSLIP", ARPHRD_CSLIP},
      {(char*)0},
      {"RAWHDLC", ARPHRD_RAWHDLC},
      {"LOOPBACK", ARPHRD_LOOPBACK},
      {"HDLC", ARPHRD_HDLC},
      {(char*)0},
      {"PIMREG", ARPHRD_PIMREG},
      {(char*)0},
      {"LOCALTLK", ARPHRD_LOCALTLK},
      {"FCPL", ARPHRD_FCPL},
      {"IEEE80211_PRISM", ARPHRD_IEEE80211_PRISM},
      {(char*)0}, {(char*)0},
      {"APPLETLK", ARPHRD_APPLETLK},
      {"SLIP", ARPHRD_SLIP},
      {"INFINIBAND", ARPHRD_INFINIBAND},
      {"CSLIP6", ARPHRD_CSLIP6},
      {(char*)0}, {(char*)0},
      {"FRAD", ARPHRD_FRAD},
      {"ADAPT", ARPHRD_ADAPT},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"VOID", ARPHRD_VOID},
      {"IPGRE", ARPHRD_IPGRE},
      {(char*)0}, {(char*)0},
      {"ATM", ARPHRD_ATM},
      {"SKIP", ARPHRD_SKIP},
      {"SLIP6", ARPHRD_SLIP6},
      {(char*)0}, {(char*)0},
      {"ASH", ARPHRD_ASH},
      {"IEEE80211", ARPHRD_IEEE80211},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"IEEE1394", ARPHRD_IEEE1394},
      {"FCAL", ARPHRD_FCAL},
      {"IEEE802154", ARPHRD_IEEE802154},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
      {"LAPB", ARPHRD_LAPB},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
      {"EUI64", ARPHRD_EUI64},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"CHAOS", ARPHRD_CHAOS}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash_arphrd_name (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].name;

          if (s && (((unsigned char)*str ^ (unsigned char)*s) & ~32) == 0 && !gperf_case_strcmp (str, s))
            return &wordlist[key];
        }
    }
  return 0;
}
