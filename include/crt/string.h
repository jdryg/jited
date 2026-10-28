#ifndef _STRING
#define _STRING

#include <stddef.h> // size_t, rsize_t, NULL
#include <errno.h>  // errno_t (Annex K)

// C11 7.24.2 Copying functions
void*  memcpy(void* s1, const void* s2, size_t n);
void*  memmove(void* s1, const void* s2, size_t n);
char*  strcpy(char* s1, const char* s2);
char*  strncpy(char* s1, const char* s2, size_t n);

// C11 7.24.3 Concatenation functions
char*  strcat(char* s1, const char* s2);
char*  strncat(char* s1, const char* s2, size_t n);

// C11 7.24.4 Comparison functions
int    memcmp(const void* s1, const void* s2, size_t n);
int    strcmp(const char* s1, const char* s2);
int    strcoll(const char* s1, const char* s2);
int    strncmp(const char* s1, const char* s2, size_t n);
size_t strxfrm(char* s1, const char* s2, size_t n);

// C11 7.24.5 Search functions
void*  memchr(const void* s, int c, size_t n);
char*  strchr(const char* s, int c);
size_t strcspn(const char* s1, const char* s2);
char*  strpbrk(const char* s1, const char* s2);
char*  strrchr(const char* s, int c);
size_t strspn(const char* s1, const char* s2);
char*  strstr(const char* s1, const char* s2);
char*  strtok(char* s1, const char* s2);

// C11 7.24.6 Miscellaneous functions
void*  memset(void* s, int c, size_t n);
char*  strerror(int errnum);
size_t strlen(const char* s);

// C11 K.3.7
errno_t memcpy_s(void* s1, rsize_t s1max, const void* s2, rsize_t n);
errno_t memmove_s(void* s1, rsize_t s1max, const void* s2, rsize_t n);
errno_t strcpy_s(char* s1, rsize_t s1max, const char* s2);
errno_t strncpy_s(char* s1, rsize_t s1max, const char* s2, rsize_t n);
errno_t strcat_s(char* s1, rsize_t s1max, const char* s2);
errno_t strncat_s(char* s1, rsize_t s1max, const char* s2, rsize_t n);
char*   strtok_s(char* s1, rsize_t* s1max, const char* s2, char** ptr);
errno_t memset_s(void* s, rsize_t smax, int c, rsize_t n);
errno_t strerror_s(char* s, rsize_t maxsize, errno_t errnum);
size_t  strerrorlen_s(errno_t errnum);
size_t  strnlen_s(const char* s, size_t maxsize);

#ifdef _WIN32
int   _stricmp(const char* s1, const char* s2);
int   _strnicmp(const char* s1, const char* s2, size_t n);
char* _strdup(const char* s);
#define strdup _strdup
#endif // _WIN32

#endif // _STRING
