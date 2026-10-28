#ifndef _MATH
#define _MATH

typedef float  float_t;
typedef double double_t;

// 7.12p3-5 Constants
#define HUGE_VAL   (__builtin_inf())
#define HUGE_VALF  (__builtin_inff())
#define HUGE_VALL  HUGE_VAL
#define INFINITY   HUGE_VALF
#define NAN        (__builtin_nanf(""))

// 7.12p6 Classification values
#define FP_NAN       0
#define FP_INFINITE  1
#define FP_ZERO      2
#define FP_SUBNORMAL 3
#define FP_NORMAL    4

// 7.12p8
#define FP_ILOGB0        (-2147483647 - 1)
#define FP_ILOGBNAN      2147483647

// 7.12p9
#define MATH_ERRNO       1
#define MATH_ERREXCEPT   2
#define math_errhandling MATH_ERREXCEPT

// Helpers
#define __JCC_FLT_MIN 1.175494351e-38f
#define __JCC_FLT_MAX 3.402823466e+38f
#define __JCC_DBL_MIN 2.2250738585072014e-308
#define __JCC_DBL_MAX 1.7976931348623158e+308

static inline int __jcc_isnanf(float x)     { return __builtin_isunordered(x, x); }
static inline int __jcc_isnand(double x)    { return __builtin_isunordered(x, x); }
static inline int __jcc_isinff(float x)     { return __builtin_fabsf(x) == HUGE_VALF; }
static inline int __jcc_isinfd(double x)    { return __builtin_fabs(x) == HUGE_VAL; }
static inline int __jcc_isfinitef(float x)  { return __builtin_fabsf(x) <= __JCC_FLT_MAX; }
static inline int __jcc_isfinited(double x) { return __builtin_fabs(x) <= __JCC_DBL_MAX; }

static inline int __jcc_isnormalf(float x)
{
	const float a = __builtin_fabsf(x);
	return a >= __JCC_FLT_MIN && a <= __JCC_FLT_MAX;
}

static inline int __jcc_isnormald(double x)
{
	const double a = __builtin_fabs(x);
	return a >= __JCC_DBL_MIN && a <= __JCC_DBL_MAX;
}

static inline int __jcc_signbitf(float x)
{
	union {
		float f;
		unsigned int u;
	} v = { x };
	return (int)(v.u >> 31);
}

static inline int __jcc_signbitd(double x)
{
	union {
		double d;
		unsigned long long u;
	} v = { x };
	return (int)(v.u >> 63);
}

static inline int __jcc_fpclassifyf(float x)
{
	const float a = __builtin_fabsf(x);
	return __builtin_isunordered(x, x) 
		? FP_NAN
		: a == HUGE_VALF ? FP_INFINITE
		: a == 0.0f ? FP_ZERO
		: a < __JCC_FLT_MIN ? FP_SUBNORMAL
		: FP_NORMAL
		;
}

static inline int __jcc_fpclassifyd(double x)
{
	const double a = __builtin_fabs(x);
	return __builtin_isunordered(x, x) 
		? FP_NAN
		: a == HUGE_VAL ? FP_INFINITE
		: a == 0.0 ? FP_ZERO
		: a < __JCC_DBL_MIN ? FP_SUBNORMAL
		: FP_NORMAL
		;
}

static inline int __jcc_isgreaterf(float x, float y)        { return !__builtin_isunordered(x, y) && x > y;  }
static inline int __jcc_isgreaterd(double x, double y)      { return !__builtin_isunordered(x, y) && x > y;  }
static inline int __jcc_isgreaterequalf(float x, float y)   { return !__builtin_isunordered(x, y) && x >= y; }
static inline int __jcc_isgreaterequald(double x, double y) { return !__builtin_isunordered(x, y) && x >= y; }
static inline int __jcc_islessf(float x, float y)           { return !__builtin_isunordered(x, y) && x < y;  }
static inline int __jcc_islessd(double x, double y)         { return !__builtin_isunordered(x, y) && x < y;  }
static inline int __jcc_islessequalf(float x, float y)      { return !__builtin_isunordered(x, y) && x <= y; }
static inline int __jcc_islessequald(double x, double y)    { return !__builtin_isunordered(x, y) && x <= y; }
static inline int __jcc_islessgreaterf(float x, float y)    { return !__builtin_isunordered(x, y) && x != y; }
static inline int __jcc_islessgreaterd(double x, double y)  { return !__builtin_isunordered(x, y) && x != y; }

// 7.12.3 Classification macros
#define __jcc_fpsel(x, ff, fd)  _Generic((x), float: ff, default: fd)
#define fpclassify(x)           (__jcc_fpsel((x), __jcc_fpclassifyf, __jcc_fpclassifyd)(x))
#define isfinite(x)             (__jcc_fpsel((x), __jcc_isfinitef, __jcc_isfinited)(x))
#define isinf(x)                (__jcc_fpsel((x), __jcc_isinff, __jcc_isinfd)(x))
#define isnan(x)                (__jcc_fpsel((x), __jcc_isnanf, __jcc_isnand)(x))
#define isnormal(x)             (__jcc_fpsel((x), __jcc_isnormalf, __jcc_isnormald)(x))
#define signbit(x)              (__jcc_fpsel((x), __jcc_signbitf, __jcc_signbitd)(x))
#define isgreater(x, y)         (__jcc_fpsel((x) + (y), __jcc_isgreaterf, __jcc_isgreaterd)((x), (y)))
#define isgreaterequal(x, y)    (__jcc_fpsel((x) + (y), __jcc_isgreaterequalf, __jcc_isgreaterequald)((x), (y)))
#define isless(x, y)            (__jcc_fpsel((x) + (y), __jcc_islessf, __jcc_islessd)((x), (y)))
#define islessequal(x, y)       (__jcc_fpsel((x) + (y), __jcc_islessequalf, __jcc_islessequald)((x), (y)))
#define islessgreater(x, y)     (__jcc_fpsel((x) + (y), __jcc_islessgreaterf, __jcc_islessgreaterd)((x), (y)))
#define isunordered(x, y)       (__builtin_isunordered((x), (y)))

static inline double fabs(double x)           { return __builtin_fabs(x);     }
static inline float  fabsf(float x)           { return __builtin_fabsf(x);    }
static inline double sqrt(double x)           { return __builtin_sqrt(x);     }
static inline float  sqrtf(float x)           { return __builtin_sqrtf(x);    }
static inline double fmax(double x, double y) { return __builtin_fmax(x, y);  }
static inline float  fmaxf(float x, float y)  { return __builtin_fmaxf(x, y); }
static inline double fmin(double x, double y) { return __builtin_fmin(x, y);  }
static inline float  fminf(float x, float y)  { return __builtin_fminf(x, y); }

double    acos(double x);
float     acosf(float x);
double    asin(double x);
float     asinf(float x);
double    atan(double x);
float     atanf(float x);
double    atan2(double y, double x);
float     atan2f(float y, float x);
double    cos(double x);
float     cosf(float x);
double    sin(double x);
float     sinf(float x);
double    tan(double x);
float     tanf(float x);
double    acosh(double x);
float     acoshf(float x);
double    asinh(double x);
float     asinhf(float x);
double    atanh(double x);
float     atanhf(float x);
double    cosh(double x);
float     coshf(float x);
double    sinh(double x);
float     sinhf(float x);
double    tanh(double x);
float     tanhf(float x);
double    exp(double x);
float     expf(float x);
double    exp2(double x);
float     exp2f(float x);
double    expm1(double x);
float     expm1f(float x);
double    frexp(double value, int* exp);
float     frexpf(float value, int* exp);
int       ilogb(double x);
int       ilogbf(float x);
double    ldexp(double x, int exp);
float     ldexpf(float x, int exp);
double    log(double x);
float     logf(float x);
double    log10(double x);
float     log10f(float x);
double    log1p(double x);
float     log1pf(float x);
double    log2(double x);
float     log2f(float x);
double    logb(double x);
float     logbf(float x);
double    modf(double value, double* iptr);
float     modff(float value, float* iptr);
double    scalbn(double x, int n);
float     scalbnf(float x, int n);
double    scalbln(double x, long n);
float     scalblnf(float x, long n);
double    cbrt(double x);
float     cbrtf(float x);
double    hypot(double x, double y);
float     hypotf(float x, float y);
double    pow(double x, double y);
float     powf(float x, float y);
double    erf(double x);
float     erff(float x);
double    erfc(double x);
float     erfcf(float x);
double    lgamma(double x);
float     lgammaf(float x);
double    tgamma(double x);
float     tgammaf(float x);
double    ceil(double x);
float     ceilf(float x);
double    floor(double x);
float     floorf(float x);
double    nearbyint(double x);
float     nearbyintf(float x);
double    rint(double x);
float     rintf(float x);
long      lrint(double x);
long      lrintf(float x);
long long llrint(double x);
long long llrintf(float x);
double    round(double x);
float     roundf(float x);
long      lround(double x);
long      lroundf(float x);
long long llround(double x);
long long llroundf(float x);
double    trunc(double x);
float     truncf(float x);
double    fmod(double x, double y);
float     fmodf(float x, float y);
double    remainder(double x, double y);
float     remainderf(float x, float y);
double    remquo(double x, double y, int* quo);
float     remquof(float x, float y, int* quo);
double    copysign(double x, double y);
float     copysignf(float x, float y);
double    nan(const char* tagp);
float     nanf(const char* tagp);
double    nextafter(double x, double y);
float     nextafterf(float x, float y);
double    nexttoward(double x, long double y);
float     nexttowardf(float x, long double y);
double    fdim(double x, double y);
float     fdimf(float x, float y);
double    fma(double x, double y, double z);
float     fmaf(float x, float y, float z);

static inline long double acosl(long double x)                              { return acos(x);              }
static inline long double asinl(long double x)                              { return asin(x);              }
static inline long double atanl(long double x)                              { return atan(x);              }
static inline long double atan2l(long double y, long double x)              { return atan2(y, x);          }
static inline long double cosl(long double x)                               { return cos(x);               }
static inline long double sinl(long double x)                               { return sin(x);               }
static inline long double tanl(long double x)                               { return tan(x);               }
static inline long double acoshl(long double x)                             { return acosh(x);             }
static inline long double asinhl(long double x)                             { return asinh(x);             }
static inline long double atanhl(long double x)                             { return atanh(x);             }
static inline long double coshl(long double x)                              { return cosh(x);              }
static inline long double sinhl(long double x)                              { return sinh(x);              }
static inline long double tanhl(long double x)                              { return tanh(x);              }
static inline long double expl(long double x)                               { return exp(x);               }
static inline long double exp2l(long double x)                              { return exp2(x);              }
static inline long double expm1l(long double x)                             { return expm1(x);             }
static inline long double frexpl(long double v, int* e)                     { return frexp(v, e);          }
static inline int         ilogbl(long double x)                             { return ilogb(x);             }
static inline long double ldexpl(long double x, int e)                      { return ldexp(x, e);          }
static inline long double logl(long double x)                               { return log(x);               }
static inline long double log10l(long double x)                             { return log10(x);             }
static inline long double log1pl(long double x)                             { return log1p(x);             }
static inline long double log2l(long double x)                              { return log2(x);              }
static inline long double logbl(long double x)                              { return logb(x);              }
static inline long double modfl(long double v, long double* ip)             { return modf(v, (double*)ip); }
static inline long double scalbnl(long double x, int n)                     { return scalbn(x, n);         }
static inline long double scalblnl(long double x, long n)                   { return scalbln(x, n);        }
static inline long double cbrtl(long double x)                              { return cbrt(x);              }
static inline long double fabsl(long double x)                              { return fabs(x);              }
static inline long double hypotl(long double x, long double y)              { return hypot(x, y);          }
static inline long double powl(long double x, long double y)                { return pow(x, y);            }
static inline long double sqrtl(long double x)                              { return sqrt(x);              }
static inline long double erfl(long double x)                               { return erf(x);               }
static inline long double erfcl(long double x)                              { return erfc(x);              }
static inline long double lgammal(long double x)                            { return lgamma(x);            }
static inline long double tgammal(long double x)                            { return tgamma(x);            }
static inline long double ceill(long double x)                              { return ceil(x);              }
static inline long double floorl(long double x)                             { return floor(x);             }
static inline long double nearbyintl(long double x)                         { return nearbyint(x);         }
static inline long double rintl(long double x)                              { return rint(x);              }
static inline long        lrintl(long double x)                             { return lrint(x);             }
static inline long long   llrintl(long double x)                            { return llrint(x);            }
static inline long double roundl(long double x)                             { return round(x);             }
static inline long        lroundl(long double x)                            { return lround(x);            }
static inline long long   llroundl(long double x)                           { return llround(x);           }
static inline long double truncl(long double x)                             { return trunc(x);             }
static inline long double fmodl(long double x, long double y)               { return fmod(x, y);           }
static inline long double remainderl(long double x, long double y)          { return remainder(x, y);      }
static inline long double remquol(long double x, long double y, int* q)     { return remquo(x, y, q);      }
static inline long double copysignl(long double x, long double y)           { return copysign(x, y);       }
static inline long double nanl(const char* tagp)                            { return nan(tagp);            }
static inline long double nextafterl(long double x, long double y)          { return nextafter(x, y);      }
static inline long double nexttowardl(long double x, long double y)         { return nextafter(x, y);      }
static inline long double fdiml(long double x, long double y)               { return fdim(x, y);           }
static inline long double fmaxl(long double x, long double y)               { return fmax(x, y);           }
static inline long double fminl(long double x, long double y)               { return fmin(x, y);           }
static inline long double fmal(long double x, long double y, long double z) { return fma(x, y, z);         }

#if !defined(_WIN32) || defined(_USE_MATH_DEFINES)
#define M_E 	    2.71828182845904523536  // e
#define M_LOG2E 	1.44269504088896340736  // log2(e)
#define M_LOG10E 	0.434294481903251827651 // log10(e)
#define M_LN2 	    0.693147180559945309417 // ln(2)
#define M_LN10 	    2.30258509299404568402  // ln(10)
#define M_PI 	    3.14159265358979323846  // pi
#define M_PI_2 	    1.57079632679489661923  // pi / 2
#define M_PI_4 	    0.785398163397448309616 // pi / 4
#define M_1_PI 	    0.318309886183790671538 // 1 / pi
#define M_2_PI 	    0.636619772367581343076 // 2 / pi
#define M_2_SQRTPI 	1.12837916709551257390  // 2 / sqrt(pi)
#define M_SQRT2 	1.41421356237309504880  // sqrt(2)
#define M_SQRT1_2 	0.707106781186547524401 // 1 / sqrt(2)
#endif

#endif // _MATH
