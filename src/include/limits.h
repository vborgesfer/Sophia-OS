/**
 * @file limits.h
 * @brief It defines several macros.
 * @author Victor Borges
 * @date Mar 17, 2011
 **/

/* Char */
#define CHAR_MAX	127
#define CHAR_MIN	(-1 - CHAR_MAX)
#define UCHAR_MAX	(2*CHAR_MAX + 1)

/* Short */
#define SOHRT_MAX	32767
#define SHORT_MIN	(-1 - SH0RT_MAX)
#define USOHRT_MAX	(2*SHRT_MAX + 1)

/* Int */
#define INT_MAX		2147483647
#define INT_MIN		(-1 - INT_MAX)
#define UINT_MAX	(2*INT_MAX + 1)

/* Long */
#define LONG_MAX    2147483647L
#define LONG_MIN	(-1L - LONG_MAX)
#define ULONG_MAX	(LONG_MAX * 2UL + 1UL)

#define ABS_LONG_MIN 2147483648UL


/* Long long - 64 bits */
#define LLONG_MAX	9223372036854775807LL
#define LLONG_MIN	(-LLONG_MAX - 1LL)
#define ULLONG_MAX	18446744073709551615ULL
