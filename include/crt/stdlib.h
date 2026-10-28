#ifndef _STDLIB
#define _STDLIB

#include <stddef.h> // size_t, wchar_t, NULL

typedef struct div_t 
{
	int quot; 
	int rem; 
} div_t;

typedef struct ldiv_t 
{ 
	long quot;
	long rem;
} ldiv_t;

typedef struct lldiv_t
{ 
	long long quot; 
	long long rem; 
} lldiv_t;

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define RAND_MAX     0x7fff

size_t __jcc_mb_cur_max(void);
#define MB_CUR_MAX (__jcc_mb_cur_max())

// C11 7.22.1 Numeric conversion functions
double             atof(const char* nptr);
int                atoi(const char* nptr);
long               atol(const char* nptr);
long long          atoll(const char* nptr);
double             strtod(const char* nptr, char** endptr);
float              strtof(const char* nptr, char** endptr);
long double        strtold(const char* nptr, char** endptr);
long               strtol(const char* nptr, char** endptr, int base);
long long          strtoll(const char* nptr, char** endptr, int base);
unsigned long      strtoul(const char* nptr, char** endptr, int base);
unsigned long long strtoull(const char* nptr, char** endptr, int base);

// C11 7.22.2 Pseudo-random sequence generation functions
int                rand(void);
void               srand(unsigned int seed);

// C11 7.22.3 Memory management functions
void*              aligned_alloc(size_t alignment, size_t size);
void*              calloc(size_t nmemb, size_t size);
void               free(void* ptr);
void*              malloc(size_t size);
void*              realloc(void* ptr, size_t size);

// C11 7.22.4 Communication with the environment
_Noreturn void     abort(void);
int                atexit(void (*func)(void));
int                at_quick_exit(void (*func)(void));
_Noreturn void     exit(int status);
_Noreturn void     _Exit(int status);
char*              getenv(const char* name);
_Noreturn void     quick_exit(int status);
int                system(const char* string);

// C11 7.22.5 Searching and sorting utilities
void*              bsearch(const void* key, const void* base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));
void               qsort(void* base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));

// C11 7.22.6 Integer arithmetic functions
int                abs(int j);
long               labs(long j);
long long          llabs(long long j);
div_t              div(int numer, int denom);
ldiv_t             ldiv(long numer, long denom);
lldiv_t            lldiv(long long numer, long long denom);

// C11 7.22.7 Multibyte/wide character conversion functions
int                mblen(const char* s, size_t n);
int                mbtowc(wchar_t* pwc, const char* s, size_t n);
int                wctomb(char* s, wchar_t wc);

// C11 7.22.8 Multibyte/wide string conversion functions
size_t             mbstowcs(wchar_t* pwcs, const char* s, size_t n);
size_t             wcstombs(char* s, const wchar_t* pwcs, size_t n);

#endif // _STDLIB
