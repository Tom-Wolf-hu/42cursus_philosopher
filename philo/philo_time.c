/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarkas <tfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:14:50 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/10 18:15:50 by tfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

long	get_current_time(void)
{
	struct timeval	current;
	long			time_in_ms;

	if (gettimeofday(&current, NULL) == -1)
	{
		write_stderr("Get the current time function Failed.\n");
		return (-1);
	}
	time_in_ms = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	printf("The current time in get_current_time function: %ld.\n", time_in_ms);
	return (time_in_ms);
}

long	my_usleep(long sleep_time_ms)
{
	long	start_sleep;
	long	end_sleep;

	start_sleep = get_current_time();
	if (sleep_time_ms > 10)
		usleep(sleep_time_ms * 1000 - 10000);
	while (1)
	{
		end_sleep = get_current_time();
		if (end_sleep >= start_sleep + sleep_time_ms)
			return (end_sleep);
		continue ;
	}
	return (-1);
}
