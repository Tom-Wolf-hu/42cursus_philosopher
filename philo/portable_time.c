#ifdef _WIN32
#include "philo_header.h"
#include <time.h>

int	gettimeofday(struct timeval *tp, void *tzp)
{
    FILETIME ft;
    ULARGE_INTEGER tmpres = {0};
    const ULONGLONG EPOCH_DIFF_1970 = 116444736000000000ULL;
	const ULONGLONG EPOCH_DIFF_2000 = 946684800ULL; // seconds from 1970 to 2000

    if (tp == NULL)
	{
		write_stderr("tp is NULL in WIN gettimeofday.");
		return (-1);
	}

    GetSystemTimeAsFileTime(&ft);
    tmpres.LowPart = ft.dwLowDateTime;
    tmpres.HighPart = ft.dwHighDateTime;

    // Convert from Windows epoch to Unix epoch
    tmpres.QuadPart -= EPOCH_DIFF_1970;
    tmpres.QuadPart /= 10;  // Convert to microseconds

    tp->tv_sec = (long)((tmpres.QuadPart / 1000000UL) - EPOCH_DIFF_2000);
    tp->tv_usec = (long)(tmpres.QuadPart % 1000000UL);

    return (0);
}
#endif