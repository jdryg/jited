#ifndef _TIME
#define _TIME

#include <stddef.h>   // size_t, NULL
#include <errno.h>    // errno_t (Annex K)

typedef long long  __time64_t;
typedef __time64_t time_t;
typedef long       clock_t;

#define CLOCKS_PER_SEC ((clock_t)1000)
#define TIME_UTC       1

struct tm
{
	int tm_sec;    // seconds after the minute  [0, 60]
	int tm_min;    // minutes after the hour    [0, 59]
	int tm_hour;   // hours since midnight      [0, 23]
	int tm_mday;   // day of the month          [1, 31]
	int tm_mon;    // months since January      [0, 11]
	int tm_year;   // years since 1900
	int tm_wday;   // days since Sunday         [0, 6]
	int tm_yday;   // days since January 1      [0, 365]
	int tm_isdst;  // Daylight Saving Time flag
};

struct timespec
{
	time_t tv_sec;
	long   tv_nsec;
};

// 7.27.2 Time manipulation functions
clock_t clock(void);
double  difftime(time_t time1, time_t time0);
time_t  mktime(struct tm* timeptr);
time_t  time(time_t* timer);
int     timespec_get(struct timespec* ts, int base);

// 7.27.3 Time conversion functions
char*      asctime(const struct tm* timeptr);
char*      ctime(const time_t* timer);
struct tm* gmtime(const time_t* timer);
struct tm* localtime(const time_t* timer);
size_t     strftime(char* s, size_t maxsize, const char* format, const struct tm* timeptr);

// K.3.8 Bounds-checking interfaces.
errno_t    asctime_s(char* s, rsize_t maxsize, const struct tm* timeptr);
errno_t    ctime_s(char* s, rsize_t maxsize, const time_t* timer);
struct tm* gmtime_s(const time_t* timer, struct tm* result);
struct tm* localtime_s(const time_t* timer, struct tm* result);

#endif // _TIME
