#ifdef _WIN32
# include "portable.h"

int gettimeofday(struct timeval *tp, void *tzp)
{
    FILETIME        ft;
    ULARGE_INTEGER  uli;
    long long       time_since_1601;
    long long       seconds_since_1970;

    if (tp == NULL) 
    {
        write_stderr("tp is NULL in WIN gettimeofday.\n");
        return (-1);
    }

    GetSystemTimeAsFileTime(&ft);

    // Copy the FILETIME into a ULARGE_INTEGER.
    uli.LowPart = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;
    time_since_1601 = uli.QuadPart;

    // Convert from 100-nanosecond intervals since 1601 to seconds since 1970.
    // This is done in steps to avoid overflow.
    seconds_since_1970 = (time_since_1601 / 10000000ULL) - 11644473600ULL; // Corrected offset

    tp->tv_sec = (long)seconds_since_1970;
    tp->tv_usec = (long)((time_since_1601 % 10000000ULL) / 10); // Get remaining 100-nanoseconds and convert to microseconds

    printf("the tv_sec: %ld\tthe tv_usec: %ld\n", tp->tv_sec, tp->tv_usec);
    fflush(stdout); // Ensure printf output is flushed

    ssize_t bytes_written = write(1, "hello\n", 6);
    if (bytes_written != 6) 
    {
        write_stderr("write() failed or didn't write all bytes.\n");
    }
    
    return (0);
}

#endif