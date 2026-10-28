#ifndef _LIMITS_H
#define _LIMITS_H

// C11 5.2.4.2.1 Sizes of integer types.
#define CHAR_BIT    8
#define MB_LEN_MAX  5 // maximum number of bytes in a multibyte character, for any supported locale (MSVC)

#define SCHAR_MIN   (-127 - 1)
#define SCHAR_MAX   127
#define UCHAR_MAX   0xff

// If the value of an object of type char is treated as a signed integer when used in an
// expression, the value of CHAR_MIN shall be the same as that of SCHAR_MIN and the
// value of CHAR_MAX shall be the same as that of SCHAR_MAX.
#define CHAR_MIN    SCHAR_MIN
#define CHAR_MAX    SCHAR_MAX

#define SHRT_MIN    (-32767 - 1)
#define SHRT_MAX    32767
#define USHRT_MAX   0xFFFF

#define INT_MIN     (-2147483647 - 1)
#define INT_MAX     2147483647
#define UINT_MAX    0xFFFFFFFFu

#define LONG_MIN    (-2147483647l - 1)
#define LONG_MAX    2147483647l
#define ULONG_MAX   0xFFFFFFFFul

#define LLONG_MIN   (-9223372036854775807ll - 1)
#define LLONG_MAX   9223372036854775807ll
#define ULLONG_MAX  0xFFFFFFFFFFFFFFFFull

#endif // _LIMITS_H
