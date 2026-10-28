#ifndef _STDARG_H
#define _STDARG_H

#include <stdint.h>

#if defined(_WIN64)
typedef char* va_list;
#else
typedef struct {
    unsigned int gp_offset;
    unsigned int fp_offset;
    void* overflow_arg_area;
    void* reg_save_area;
} __va_elem;

typedef __va_elem va_list[1];
#endif

#define va_start(ap, ...)  __builtin_va_start(ap)
#define va_end(ap)         __builtin_va_end(ap)
#define va_arg(ap, ty)     __builtin_va_arg(ap, ty)
#define va_copy(dest, src) __builtin_va_copy(dest, src)

#endif
