/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarkas <tfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:02:05 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/08 20:38:15 by tfarkas          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_input	in_args;
	long	time_in_ms1;
	long	time_in_ms2;
	long	time_in_ms3;

	if (!check_input(argc, argv, &in_args))
		return (1);
	time_in_ms1 = get_current_time();
	printf("This is the store input: %d\n", in_args.die_t);
	printf("The 0.current time is: %ld\n", time_in_ms1);
	my_usleep(30);
	time_in_ms2 = get_current_time();
	printf("The 1.current time is: %ld\n", time_in_ms2);
	printf("The elapsed time is: %ld\n", time_in_ms2 - time_in_ms1);
	my_usleep(50);
	time_in_ms3 = get_current_time();
	printf("The 2.current time is: %ld\n", time_in_ms3);
	printf("The elapsed time is: %ld\n", time_in_ms3 - time_in_ms1);
	return (0);
}

// long	time_diff12;
// long	time_diff13;
// usleep(30000);
// usleep(50000);
// time_diff12 = get_time_diff(time_in_ms1, time_in_ms2);
// time_diff13 = get_time_diff(time_in_ms1, time_in_ms3);