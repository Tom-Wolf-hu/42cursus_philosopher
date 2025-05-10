/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarkas <tfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:17:24 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/10 18:27:45 by tfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	one_philo(long start_t,long die_t)
{
	long	current_t;

	current_t = get_current_time();
	if (current_t < 0)
		return (-1);
	print_message(current_t - start_t, 1, FORK);
	my_usleep(die_t);
	usleep(1000);
	current_t = get_current_time();
	if (current_t < 0)
		return (-1);
	print_message(current_t - start_t, 1, DIE);
	return (0);
}

void	print_message(long time_ms, int philo_num, t_state message)
{
	if (message == FORK)
		printf("%ld %d has taken a fork\n", time_ms, philo_num);
	else if (message == EAT)
		printf("%ld %d is eating\n", time_ms, philo_num);
	else if (message == SLEEP)
		printf("%ld %d is sleeping\n", time_ms, philo_num);
	else if (message == THINK)
		printf("%ld %d is thinking\n", time_ms, philo_num);
	else if (message == DIE)
		printf("\033[1;31m%ld %d is died\033[0m\n", time_ms, philo_num);
}

void	*testfunc(void *arg)
{
	(void) arg;
	print_message(12, 3, FORK);
	usleep(20000);
	print_message(12, 4, THINK);
	usleep(20000);
	print_message(12, 3, DIE);
	return (NULL);
}
