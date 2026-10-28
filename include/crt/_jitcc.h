#ifndef __JITCC_H
#define __JITCC_H

#undef __cdecl
#undef _X86_
#undef WIN32

#include <stddef.h>
#include <stdarg.h>
#include <time.h>

#define _HAVE_INT64

#define __cdecl
#define __declspec(x) __attribute__((x))

#undef _MSVCRT_

#define __CRT_INLINE extern inline

#define DECLSPEC_ALIGN(x) __attribute__((aligned(x)))
#define _CRT_PACKING 8
#define __CRT_UNALIGNED

#define __CRT_STRINGIZE(_Value) #_Value
#define _CRT_STRINGIZE(_Value) __CRT_STRINGIZE(_Value)
#define __CRT_WIDE(_String) L ## _String
#define _CRT_WIDE(_String) __CRT_WIDE(_String)

#define __stdcall
#define _AMD64_ 1
#define __x86_64 1
#define __TRY__

#define _INTEGRAL_MAX_BITS 64

#ifndef _WCTYPE_T_DEFINED
#define _WCTYPE_T_DEFINED
typedef wchar_t wctype_t;
#endif

// for winapi
#define DECLSPEC_NORETURN
#define NOSERVICE 1
#define NOMCX 1
#define NOIME 1
#ifndef WINVER
# define WINVER 0x0502
#endif
#ifndef _WIN32_WINNT
# define _WIN32_WINNT 0x502
#endif

#define WINAPI_FAMILY_PARTITION(X) 1

#endif // __JITCC_H
