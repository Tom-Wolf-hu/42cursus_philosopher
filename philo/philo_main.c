/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarkas <tfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:02:05 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/08 14:37:55 by tfarkas          ###   ########.fr       */
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
	time_in_ms = current.tv_sec * 1000000 + current.tv_usec / 1000;
	return (time_in_ms);
}

int	main(int argc, char **argv)
{
	t_input	in_args;
	long	time_in_ms;

	if (!check_input(argc, argv, &in_args))
		return (1);
	time_in_ms = get_current_time();
	printf("This is the store input: %d\n", in_args.die_t);
	printf("The current time is: %ld\n", time_in_ms);
	return (0);
}
