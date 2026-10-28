#ifndef _FLOAT_H
#define _FLOAT_H

// C11 5.2.4.2.2 Characteristics of floating types.
#define FLT_RADIX         2
#define FLT_ROUNDS        1 // round to nearest
#define FLT_EVAL_METHOD   0

#define FLT_HAS_SUBNORM   1
#define DBL_HAS_SUBNORM   1
#define LDBL_HAS_SUBNORM  DBL_HAS_SUBNORM

#define FLT_MANT_DIG      24
#define DBL_MANT_DIG      53
#define LDBL_MANT_DIG     DBL_MANT_DIG

#define FLT_DIG           6
#define DBL_DIG           15
#define LDBL_DIG          DBL_DIG

#define FLT_DECIMAL_DIG   9
#define DBL_DECIMAL_DIG   17
#define LDBL_DECIMAL_DIG  DBL_DECIMAL_DIG
#define DECIMAL_DIG       LDBL_DECIMAL_DIG

#define FLT_MIN_EXP       (-125)
#define DBL_MIN_EXP       (-1021)
#define LDBL_MIN_EXP      DBL_MIN_EXP

#define FLT_MIN_10_EXP    (-37)
#define DBL_MIN_10_EXP    (-307)
#define LDBL_MIN_10_EXP   DBL_MIN_10_EXP

#define FLT_MAX_EXP       128
#define DBL_MAX_EXP       1024
#define LDBL_MAX_EXP      DBL_MAX_EXP

#define FLT_MAX_10_EXP    38
#define DBL_MAX_10_EXP    308
#define LDBL_MAX_10_EXP   DBL_MAX_10_EXP

#define FLT_MAX           3.402823466e+38f          // 0x1.fffffep+127
#define DBL_MAX           1.7976931348623158e+308   // 0x1.fffffffffffffp+1023
#define LDBL_MAX          DBL_MAX

#define FLT_EPSILON       1.192092896e-07f          // 0x1p-23
#define DBL_EPSILON       2.2204460492503131e-016   // 0x1p-52
#define LDBL_EPSILON      DBL_EPSILON

#define FLT_MIN           1.175494351e-38f          // 0x1p-126
#define DBL_MIN           2.2250738585072014e-308   // 0x1p-1022
#define LDBL_MIN          DBL_MIN

#define FLT_TRUE_MIN      1.401298464e-45f          // 0x1p-149
#define DBL_TRUE_MIN      4.9406564584124654e-324   // 0x1p-1074
#define LDBL_TRUE_MIN     DBL_TRUE_MIN

#endif // _FLOAT_H
