/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf -L ANSI-C -t --ignore-case -N lookup_dns_type -H hash_dns_type_name -p -C  */
/* Computed positions: -k'1-2,$' */

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

struct dns_type_name { const char* name; int id; };

#define TOTAL_KEYWORDS 77
#define MIN_WORD_LENGTH 1
#define MAX_WORD_LENGTH 10
#define MIN_HASH_VALUE 7
#define MAX_HASH_VALUE 177
/* maximum key range = 171, duplicates = 0 */

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
hash_dns_type_name (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
       25,  15,   0,  75,  50, 178,  10, 178, 178, 178,
      178, 178, 178, 178, 178,   5,  50,  30,  25,  75,
       65,  80,  75,  10, 178,  35,  75,  15,  10,  60,
        5, 178,   5,   5,   0,  65,   5,  60,  20,  35,
      178, 178, 178, 178, 178, 178, 178,   5,  50,  30,
       25,  75,  65,  80,  75,  10, 178,  35,  75,  15,
       10,  60,   5, 178,   5,   5,   0,  65,   5,  60,
       20,  35, 178, 178, 178, 178, 178, 178, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 178, 178, 178,
      178, 178, 178, 178, 178, 178
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[1]];
      /*FALLTHROUGH*/
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct dns_type_name *
lookup_dns_type (register const char *str, register unsigned int len)
{
  static const struct dns_type_name wordlist[] =
    {
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"RT", DNS_TYPE_RT},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"A", DNS_TYPE_A},
      {"TA", DNS_TYPE_TA},
      {"PTR", DNS_TYPE_PTR},
      {"ATMA", DNS_TYPE_ATMA},
      {(char*)0}, {(char*)0},
      {"RP", DNS_TYPE_RP},
      {"SRV", DNS_TYPE_SRV},
      {"AAAA", DNS_TYPE_AAAA},
      {"SSHFP", DNS_TYPE_SSHFP},
      {(char*)0},
      {"NS", DNS_TYPE_NS},
      {"TXT", DNS_TYPE_TXT},
      {"NSAP", DNS_TYPE_NSAP},
      {"NAPTR", DNS_TYPE_NAPTR},
      {(char*)0},
      {"MR", DNS_TYPE_MR},
      {"NSAP_PTR", DNS_TYPE_NSAP_PTR},
      {"ISDN", DNS_TYPE_ISDN},
      {"MAILA", DNS_TYPE_MAILA},
      {(char*)0}, {(char*)0},
      {"NXT", DNS_TYPE_NXT},
      {"AXFR", DNS_TYPE_AXFR},
      {"NSEC3", DNS_TYPE_NSEC3},
      {(char*)0},
      {"DS", DNS_TYPE_DS},
      {(char*)0},
      {"IXFR", DNS_TYPE_IXFR},
      {"NSEC3PARAM", DNS_TYPE_NSEC3PARAM},
      {(char*)0}, {(char*)0},
      {"CAA", DNS_TYPE_CAA},
      {(char*)0}, {(char*)0},
      {"TALINK", DNS_TYPE_TALINK},
      {"PX", DNS_TYPE_PX},
      {"NID", DNS_TYPE_NID},
      {"NSEC", DNS_TYPE_NSEC},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"ANY", DNS_TYPE_ANY},
      {"SINK", DNS_TYPE_SINK},
      {(char*)0},
      {"NIMLOC", DNS_TYPE_NIMLOC},
      {"MX", DNS_TYPE_MX},
      {"IPSECKEY", DNS_TYPE_IPSECKEY},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"CDS", DNS_TYPE_CDS},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"MD", DNS_TYPE_MD},
      {"OPT", DNS_TYPE_OPT},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"SOA", DNS_TYPE_SOA},
      {"TKEY", DNS_TYPE_TKEY},
      {"MAILB", DNS_TYPE_MAILB},
      {"DNSKEY", DNS_TYPE_DNSKEY},
      {"KX", DNS_TYPE_KX},
      {"SPF", DNS_TYPE_SPF},
      {"RKEY", DNS_TYPE_RKEY},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"URI", DNS_TYPE_URI},
      {"TLSA", DNS_TYPE_TLSA},
      {"NINFO", DNS_TYPE_NINFO},
      {(char*)0},
      {"LP", DNS_TYPE_LP},
      {"APL", DNS_TYPE_APL},
      {"TSIG", DNS_TYPE_TSIG},
      {"MINFO", DNS_TYPE_MINFO},
      {(char*)0}, {(char*)0},
      {"HIP", DNS_TYPE_HIP},
      {"GPOS", DNS_TYPE_GPOS},
      {"RRSIG", DNS_TYPE_RRSIG},
      {(char*)0},
      {"CDNSKEY", DNS_TYPE_CDNSKEY},
      {"SIG", DNS_TYPE_SIG},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"WKS", DNS_TYPE_WKS},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"A6", DNS_TYPE_A6},
      {"DLV", DNS_TYPE_DLV},
      {"CERT", DNS_TYPE_CERT},
      {"OPENPGPKEY", DNS_TYPE_OPENPGPKEY},
      {(char*)0}, {(char*)0},
      {"EID", DNS_TYPE_EID},
      {(char*)0},
      {"DNAME", DNS_TYPE_DNAME},
      {(char*)0},
      {"MB", DNS_TYPE_MB},
      {"L32", DNS_TYPE_L32},
      {(char*)0},
      {"CNAME", DNS_TYPE_CNAME},
      {(char*)0}, {(char*)0},
      {"X25", DNS_TYPE_X25},
      {(char*)0},
      {"AFSDB", DNS_TYPE_AFSDB},
      {(char*)0}, {(char*)0},
      {"L64", DNS_TYPE_L64},
      {(char*)0},
      {"DHCID", DNS_TYPE_DHCID},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
      {"EUI64", DNS_TYPE_EUI64},
      {(char*)0},
      {"MF", DNS_TYPE_MF},
      {"KEY", DNS_TYPE_KEY},
      {(char*)0},
      {"HINFO", DNS_TYPE_HINFO},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"NULL", DNS_TYPE_NULL},
      {"EUI48", DNS_TYPE_EUI48},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"LOC", DNS_TYPE_LOC},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"MG", DNS_TYPE_MG}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash_dns_type_name (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].name;

          if (s && (((unsigned char)*str ^ (unsigned char)*s) & ~32) == 0 && !gperf_case_strcmp (str, s))
            return &wordlist[key];
        }
    }
  return 0;
}
