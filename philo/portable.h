#pragma once

#ifdef _WIN32
# include <windows.h>

int	gettimeofday(struct timeval *tp, void *tzp);

# else
# include <sys/time.h>

#endif
