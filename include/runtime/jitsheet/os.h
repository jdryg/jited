// TODO: Remove and replace with jlib/os.h
#ifndef JITSHEET_OS_H
#define JITSHEET_OS_H

#include <stdint.h>

typedef enum os_time_units
{
	OS_TIME_UNITS_SEC = 0,
	OS_TIME_UNITS_MS,
	OS_TIME_UNITS_US,
	OS_TIME_UNITS_NS
} os_time_units;

int64_t os_timeNow(void);
int64_t os_timeDiff(int64_t end, int64_t start);
int64_t os_timeSince(int64_t start);
double  os_timeConvertTo(int64_t delta, os_time_units units);

#endif // JITSHEET_OS_H
