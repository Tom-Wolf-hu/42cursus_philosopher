#pragma once

#ifdef _WIN32
# include <windows.h>
# include <time.h>
# include <unistd.h>
# include <stdio.h>

void	write_stderr(char *str);
int		gettimeofday(struct timeval *tp, void *tzp);

# else
# include <sys/time.h>

#endif
