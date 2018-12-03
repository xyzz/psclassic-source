/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf -L ANSI-C -t --ignore-case -N lookup_errno -H hash_errno_name -p -C  */
/* Computed positions: -k'2-3,5-6' */

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

struct errno_name { const char* name; int id; };

#define TOTAL_KEYWORDS 134
#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 15
#define MIN_HASH_VALUE 6
#define MAX_HASH_VALUE 326
/* maximum key range = 321, duplicates = 0 */

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
hash_errno_name (register const char *str, register unsigned int len)
{
  static const unsigned short asso_values[] =
    {
      327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
       30, 110, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327,  25,  70,  65,  10,  10,
      105,  35,  30,   5, 327, 155,  50,  80,   0,   0,
       30, 175,   5,  35,  20, 160,  25, 105, 115,  90,
      327, 327, 327, 327, 327, 327, 327,  25,  70,  65,
       10,  10, 105,  35,  30,   5, 327, 155,  50,  80,
        0,   0,  30, 175,   5,  35,  20, 160,  25, 105,
      115,  90, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
      327, 327, 327, 327, 327, 327
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[5]];
      /*FALLTHROUGH*/
      case 5:
        hval += asso_values[(unsigned char)str[4]];
      /*FALLTHROUGH*/
      case 4:
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
        hval += asso_values[(unsigned char)str[1]];
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
const struct errno_name *
lookup_errno (register const char *str, register unsigned int len)
{
  static const struct errno_name wordlist[] =
    {
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
      {"ENOANO", ENOANO},
      {(char*)0},
      {"EIO", EIO},
      {(char*)0},
      {"ENOSR", ENOSR},
      {(char*)0},
      {"ENOLINK", ENOLINK},
      {(char*)0},
      {"EDOM", EDOM},
      {"EINTR", EINTR},
      {"ENOPROTOOPT", ENOPROTOOPT},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"EINPROGRESS", EINPROGRESS},
      {"ENOTDIR", ENOTDIR},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"ENOENT", ENOENT},
      {"EDOTDOT", EDOTDOT},
      {"ENETDOWN", ENETDOWN},
      {"ENOMEDIUM", ENOMEDIUM},
      {"ENOTRECOVERABLE", ENOTRECOVERABLE},
      {"ENOSTR", ENOSTR},
      {"ENOTNAM", ENOTNAM},
      {(char*)0},
      {"ENETRESET", ENETRESET},
      {(char*)0},
      {"ENONET", ENONET},
      {(char*)0}, {(char*)0},
      {"EADV", EADV},
      {"ETIME", ETIME},
      {"ENODEV", ENODEV},
      {"EREMOTE", EREMOTE},
      {"ENOTSOCK", ENOTSOCK},
      {"EREMOTEIO", EREMOTEIO},
      {"EROFS", EROFS},
      {"ENOCSI", ENOCSI},
      {"EISCONN", EISCONN},
      {(char*)0}, {(char*)0},
      {"EPIPE", EPIPE},
      {(char*)0},
      {"ENODATA", ENODATA},
      {"EADDRNOTAVAIL", EADDRNOTAVAIL},
      {"ETIMEDOUT", ETIMEDOUT},
      {"EADDRINUSE", EADDRINUSE},
      {"EISDIR", EISDIR},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"EOPNOTSUPP", EOPNOTSUPP},
      {"EPROTO", EPROTO},
      {"ENAVAIL", ENAVAIL},
      {(char*)0}, {(char*)0},
      {"EPROTOTYPE", EPROTOTYPE},
      {"ESRMNT", ESRMNT},
      {"ENAMETOOLONG", ENAMETOOLONG},
      {"ERESTART", ERESTART},
      {"EHOSTDOWN", EHOSTDOWN},
      {"EPROTONOSUPPORT", EPROTONOSUPPORT},
      {"EAGAIN", EAGAIN},
      {(char*)0},
      {"ENOTCONN", ENOTCONN},
      {(char*)0},
      {"ESRCH", ESRCH},
      {"ENOMSG", ENOMSG},
      {"EDESTADDRREQ", EDESTADDRREQ},
      {(char*)0}, {(char*)0},
      {"ECONNRESET", ECONNRESET},
      {"ERANGE", ERANGE},
      {"ECONNREFUSED", ECONNREFUSED},
      {(char*)0}, {(char*)0},
      {"ELOOP", ELOOP},
      {"EINVAL", EINVAL},
      {"EDEADLK", EDEADLK},
      {(char*)0},
      {"EDEADLOCK", EDEADLOCK},
      {(char*)0},
      {"ELNRNG", ELNRNG},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"ENOMEM", ENOMEM},
      {(char*)0},
      {"ESTRPIPE", ESTRPIPE},
      {"ENOTEMPTY", ENOTEMPTY},
      {"EIDRM", EIDRM},
      {"ENOSPC", ENOSPC},
      {"ECONNABORTED", ECONNABORTED},
      {(char*)0},
      {"ESHUTDOWN", ESHUTDOWN},
      {"EBADR", EBADR},
      {"ENOKEY", ENOKEY},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"EBADE", EBADE},
      {"ESPIPE", ESPIPE},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"ENOTTY", ENOTTY},
      {"EREMCHG", EREMCHG},
      {"EALREADY", EALREADY},
      {(char*)0},
      {"ENXIO", ENXIO},
      {"ESTALE", ESTALE},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"EPERM", EPERM},
      {(char*)0},
      {"ENOTBLK", ENOTBLK},
      {(char*)0}, {(char*)0},
      {"EOWNERDEAD", EOWNERDEAD},
      {"ENOSYS", ENOSYS},
      {"ENOEXEC", ENOEXEC},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"ECHRNG", ECHRNG},
      {"ETOOMANYREFS", ETOOMANYREFS},
      {(char*)0}, {(char*)0},
      {"E2BIG", E2BIG},
      {"EACCES", EACCES},
      {(char*)0}, {(char*)0},
      {"EOVERFLOW", EOVERFLOW},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"EHWPOISON", EHWPOISON},
      {"ECOMM", ECOMM},
      {"EISNAM", EISNAM},
      {"ELIBACC", ELIBACC},
      {(char*)0}, {(char*)0},
      {"EXDEV", EXDEV},
      {"EL2HLT", EL2HLT},
      {"ELIBBAD", ELIBBAD},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"ECHILD", ECHILD},
      {"ELIBSCN", ELIBSCN},
      {"EMSGSIZE", EMSGSIZE},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"ELIBMAX", ELIBMAX},
      {"ENOTUNIQ", ENOTUNIQ},
      {(char*)0}, {(char*)0},
      {"ENFILE", ENFILE},
      {"ERFKILL", ERFKILL},
      {(char*)0},
      {"ECANCELED", ECANCELED},
      {(char*)0},
      {"EWOULDBLOCK", EWOULDBLOCK},
      {"EAFNOSUPPORT", EAFNOSUPPORT},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"ENETUNREACH", ENETUNREACH},
      {"EPFNOSUPPORT", EPFNOSUPPORT},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"EEXIST", EEXIST},
      {"EBADSLT", EBADSLT},
      {"ELIBEXEC", ELIBEXEC},
      {(char*)0}, {(char*)0},
      {"EKEYREVOKED", EKEYREVOKED},
      {"EKEYREJECTED", EKEYREJECTED},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"ENOPKG", ENOPKG},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"EBFONT", EBFONT},
      {"ENOTSUP", ENOTSUP},
      {(char*)0}, {(char*)0},
      {"EBADF", EBADF},
      {"EFAULT", EFAULT},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"EDQUOT", EDQUOT},
      {(char*)0},
      {"EL2NSYNC", EL2NSYNC},
      {(char*)0},
      {"EFBIG", EFBIG},
      {"EBADFD", EBADFD},
      {"EBADMSG", EBADMSG},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"EL3RST", EL3RST},
      {"EHOSTUNREACH", EHOSTUNREACH},
      {(char*)0}, {(char*)0},
      {"ESOCKTNOSUPPORT", ESOCKTNOSUPPORT},
      {"ENOLCK", ENOLCK},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
      {"EL3HLT", EL3HLT},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"EUSERS", EUSERS},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"EILSEQ", EILSEQ},
      {"ETXTBSY", ETXTBSY},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"EMFILE", EMFILE},
      {"EUNATCH", EUNATCH},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
      {"EMEDIUMTYPE", EMEDIUMTYPE},
      {"EUCLEAN", EUCLEAN},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"ENOBUFS", ENOBUFS},
      {(char*)0},
      {"EMULTIHOP", EMULTIHOP},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"EBADRQC", EBADRQC},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {"EMLINK", EMLINK},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
      {"EKEYEXPIRED", EKEYEXPIRED},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
      {"EBUSY", EBUSY},
      {"EXFULL", EXFULL}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash_errno_name (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].name;

          if (s && (((unsigned char)*str ^ (unsigned char)*s) & ~32) == 0 && !gperf_case_strcmp (str, s))
            return &wordlist[key];
        }
    }
  return 0;
}
