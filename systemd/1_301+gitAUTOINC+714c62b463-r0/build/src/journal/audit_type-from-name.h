/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf -L ANSI-C -t --ignore-case -N lookup_audit_type -H hash_audit_type_name -p -C  */
/* Computed positions: -k'1,5,8,11,$' */

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

struct audit_type_name { const char* name; int id; };

#define TOTAL_KEYWORDS 86
#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 18
#define MIN_HASH_VALUE 3
#define MAX_HASH_VALUE 178
/* maximum key range = 176, duplicates = 0 */

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
hash_audit_type_name (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179,  30, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179,   5,  65,  40,   0,   0,
       35,  35,  10,  10, 179,  45,  10,   5,  35,  35,
       35, 179,  10,  30,   0,  20,  65,  60,   0,  75,
      179, 179, 179, 179, 179,   0, 179,   5,  65,  40,
        0,   0,  35,  35,  10,  10, 179,  45,  10,   5,
       35,  35,  35, 179,  10,  30,   0,  20,  65,  60,
        0,  75, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[10]];
      /*FALLTHROUGH*/
      case 10:
      case 9:
      case 8:
        hval += asso_values[(unsigned char)str[7]];
      /*FALLTHROUGH*/
      case 7:
      case 6:
      case 5:
        hval += asso_values[(unsigned char)str[4]];
      /*FALLTHROUGH*/
      case 4:
      case 3:
      case 2:
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
const struct audit_type_name *
lookup_audit_type (register const char *str, register unsigned int len)
{
  static const struct audit_type_name wordlist[] =
    {
      {(char*)0}, {(char*)0}, {(char*)0},
      {"EOE", EOE},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"ADD", ADD},
      {"TRIM", TRIM},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"DEL", DEL},
      {"LIST", LIST},
      {"ANOM_ABEND", ANOM_ABEND},
      {(char*)0}, {(char*)0},
      {"DEL_RULE", DEL_RULE},
      {(char*)0}, {(char*)0},
      {"MAC_MAP_ADD", MAC_MAP_ADD},
      {"REPLACE", REPLACE},
      {"ADD_RULE", ADD_RULE},
      {(char*)0}, {(char*)0},
      {"MESSAGE_TEXT_MAX", MESSAGE_TEXT_MAX},
      {(char*)0},
      {"MQ_GETSETATTR", MQ_GETSETATTR},
      {(char*)0},
      {"MAC_IPSEC_EVENT", MAC_IPSEC_EVENT},
      {"MAC_IPSEC_DELSPD", MAC_IPSEC_DELSPD},
      {(char*)0},
      {"SET", SET},
      {"USER", USER},
      {"MAC_IPSEC_DELSA", MAC_IPSEC_DELSA},
      {"MAC_IPSEC_ADDSPD", MAC_IPSEC_ADDSPD},
      {"TTY_SET", TTY_SET},
      {"GET", GET},
      {(char*)0},
      {"MAC_IPSEC_ADDSA", MAC_IPSEC_ADDSA},
      {"MAC_MAP_DEL", MAC_MAP_DEL},
      {"TTY_GET", TTY_GET},
      {"CWD", CWD},
      {"MMAP", MMAP},
      {"DAEMON_END", DAEMON_END},
      {"CAPSET", CAPSET},
      {(char*)0},
      {"AVC", AVC},
      {"PATH", PATH},
      {(char*)0}, {(char*)0},
      {"SYSCALL", SYSCALL},
      {"IPC", IPC},
      {"PROCTITLE", PROCTITLE},
      {"SOCKETCALL", SOCKETCALL},
      {(char*)0},
      {"FD_PAIR", FD_PAIR},
      {"SERVICE_START", SERVICE_START},
      {(char*)0},
      {"LIST_RULES", LIST_RULES},
      {"KERNEL", KERNEL},
      {"DAEMON_ABORT", DAEMON_ABORT},
      {"SOCKADDR", SOCKADDR},
      {"INTEGRITY_DATA", INTEGRITY_DATA},
      {"MAC_POLICY_LOAD", MAC_POLICY_LOAD},
      {(char*)0},
      {"IPC_SET_PERM", IPC_SET_PERM},
      {"AVC_PATH", AVC_PATH},
      {"INTEGRITY_RULE", INTEGRITY_RULE},
      {(char*)0},
      {"EXECVE", EXECVE},
      {(char*)0},
      {"INTEGRITY_METADATA", INTEGRITY_METADATA},
      {"FEATURE_CHANGE", FEATURE_CHANGE},
      {"MAC_STATUS", MAC_STATUS},
      {"SET_FEATURE", SET_FEATURE},
      {"OBJ_PID", OBJ_PID},
      {"TTY", TTY},
      {"INTEGRITY_HASH", INTEGRITY_HASH},
      {(char*)0},
      {"GET_FEATURE", GET_FEATURE},
      {"MQ_OPEN", MQ_OPEN},
      {(char*)0},
      {"WATCH_REM", WATCH_REM},
      {"LOGIN", LOGIN},
      {(char*)0},
      {"DAEMON_START", DAEMON_START},
      {(char*)0}, {(char*)0},
      {"WATCH_LIST", WATCH_LIST},
      {(char*)0}, {(char*)0},
      {"NETFILTER_PKT", NETFILTER_PKT},
      {"ANOM_LINK", ANOM_LINK},
      {(char*)0},
      {"SELINUX_ERR", SELINUX_ERR},
      {"MAC_CONFIG_CHANGE", MAC_CONFIG_CHANGE},
      {(char*)0}, {(char*)0},
      {"MAKE_EQUIV", MAKE_EQUIV},
      {(char*)0},
      {"KERNEL_OTHER", KERNEL_OTHER},
      {"INTEGRITY_PCR", INTEGRITY_PCR},
      {(char*)0},
      {"MAC_CALIPSO_ADD", MAC_CALIPSO_ADD},
      {(char*)0},
      {"SECCOMP", SECCOMP},
      {"USER_AVC", USER_AVC},
      {(char*)0},
      {"BPRM_FCAPS", BPRM_FCAPS},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"MAC_CALIPSO_DEL", MAC_CALIPSO_DEL},
      {"ANOM_PROMISCUOUS", ANOM_PROMISCUOUS},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"MAC_CIPSOV4_ADD", MAC_CIPSOV4_ADD},
      {"INTEGRITY_STATUS", INTEGRITY_STATUS},
      {"SERVICE_STOP", SERVICE_STOP},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"SIGNAL_INFO", SIGNAL_INFO},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"MAC_CIPSOV4_DEL", MAC_CIPSOV4_DEL},
      {(char*)0}, {(char*)0},
      {"NETFILTER_CFG", NETFILTER_CFG},
      {(char*)0}, {(char*)0},
      {"MAC_UNLBL_STCADD", MAC_UNLBL_STCADD},
      {(char*)0},
      {"CONFIG_CHANGE", CONFIG_CHANGE},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
      {"WATCH_INS", WATCH_INS},
      {(char*)0},
      {"MAC_UNLBL_STCDEL", MAC_UNLBL_STCDEL},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
      {"MQ_SENDRECV", MQ_SENDRECV},
      {(char*)0},
      {"DAEMON_CONFIG", DAEMON_CONFIG},
      {"MQ_NOTIFY", MQ_NOTIFY},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
      {"MAC_UNLBL_ALLOW", MAC_UNLBL_ALLOW},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"USER_TTY", USER_TTY}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash_audit_type_name (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].name;

          if (s && (((unsigned char)*str ^ (unsigned char)*s) & ~32) == 0 && !gperf_case_strcmp (str, s))
            return &wordlist[key];
        }
    }
  return 0;
}
