/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:02:05 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/19 11:40:36 by tamas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	philo_threads(t_coll *coll)
{
	int	i;

	i = 0;
	coll->th.philo = malloc(coll->in.philo_num * sizeof(pthread_t));
	if (!coll->th.philo)
	{
		write_stderr("Malloc failed for philo threads allocation.\n");
		return (-1);
	}
	while (i < coll->in.philo_num)
	{
		if (pthread_create(&(coll->th.philo[i]), NULL,
				philos_routine, (void *)coll->ph[i]) != 0)
		{
			write_stderr("philo thread creation failed.\n");
			return (-2);
		}
		printf("\033[1;35mThe %d philo created.\033[0m\n", i + 1);
		i++;
	}
	return (0);
}

void	*print_monitor(void *arg)
{
	t_coll	*coll;
	int		i;

	i = -1;
	coll = (t_coll *)arg;
	while (coll->th.start_t < 0)
	{
		usleep(10);
		continue ;
	}
	while (++i < coll->in.philo_num)
		print_message(get_current_time() - coll->th.start_t, i + 1, THINK);
	if (coll->in.philo_num == 1)
	{
		if (one_philo(coll->th.start_t, (long)coll->in.die_t) < 0)
			return ((void *)1);
	}
	else
	{
		if (more_philo(coll) < 0)
			return ((void *)2);
	}
	return ((void *)0);
}

int	print_thread(t_coll *coll)
{
	if (pthread_create(&(coll->th.monitor), NULL,
			print_monitor, (void *)coll) != 0)
	{
		write_stderr("monitor thread creation failed.\n");
		return (-1);
	}
	if (philo_threads(coll) < 0)
		return (-2);
	coll->th.start_t = get_current_time();
	if (coll->th.start_t < 0)
	{
		write_stderr("Failed to get the start_time");
		return (-3);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_coll	coll;

	write(1, "passed0\n", 8);
	if (!check_input(argc, argv, &coll.in))
		return (1);
	write(1, "passed1\n", 8);
	if (!coll_init(&coll))
		return (1);
	write(1, "passed2\n", 8);
	if (print_thread(&coll) < 0)
		return (free_memory(&coll), 1);
	write(1, "passed3\n", 8);
	if (pthread_join(coll.th.monitor, NULL) != 0)
	{
		write_stderr("Failed to join the monitor thread.\n");
		return (1);
	}
	write(1, "passed4\n", 8);
	if (!join_philo_threads(&coll.th, coll.in.philo_num))
		return (1);
	write(1, "passed5\n", 8);
	free_memory(&coll);
	return (0);
}
