/* Determine the wordsize from the preprocessor defines.  */

#if defined __arch64__ || defined __sparcv9
# define __WORDSIZE	64
# define __WORDSIZE_TIME64_COMPAT32	1
#else
# define __WORDSIZE	32
#endif