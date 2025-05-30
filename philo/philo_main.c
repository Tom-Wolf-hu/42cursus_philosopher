/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarkas <tfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:02:05 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/20 11:38:41 by tfarkas          ###   ########.fr       */
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
		i++;
	}
	return (0);
}

static int	wait_get_th_start_t(t_coll	*coll)
{
	if (pthread_mutex_lock(&coll->start) != 0)
	{
		write_stderr("Failed to lock start mutex.\n");
		return (-1);
	}
	while (coll->th.start_t < 0)
	{
		if (pthread_mutex_unlock(&coll->start) != 0)
		{
			write_stderr("Failed to unlock start mutex.\n");
			return (-1);
		}
		usleep(100);
		if (pthread_mutex_lock(&coll->start) != 0)
		{
			write_stderr("Failed to lock start mutex.\n");
			return (-1);
		}
	}
	if (pthread_mutex_unlock(&coll->start) != 0)
	{
		write_stderr("Failed to unlock start mutex.\n");
		return (-1);
	}
	return (0);
}

void	*print_monitor(void *arg)
{
	t_coll	*coll;
	int		i;

	i = -1;
	coll = (t_coll *)arg;
	if (wait_get_th_start_t(coll) < 0)
		return (coll->th.exit_status = 1, (void *)1);
	while (++i < coll->in.philo_num)
		print_message(get_current_time() - coll->th.start_t, i + 1, THINK);
	if (coll->in.philo_num == 1)
	{
		if (one_philo(coll->th.start_t, (long)coll->in.die_t) < 0)
			return (coll->th.exit_status = 2, (void *)1);
	}
	else
	{
		if (more_philo(coll) < 0)
			return (coll->th.exit_status = 3, (void *)2);
	}
	return (coll->th.exit_status = 0, (void *)0);
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
	if (pthread_mutex_lock(&coll->start) != 0)
	{
		write_stderr("Failed to lock start mutex.\n");
		return (-3);
	}
	coll->th.start_t = get_current_time();
	if (pthread_mutex_unlock(&coll->start) != 0)
	{
		write_stderr("Failed to unlock start mutex.\n");
		return (-4);
	}
	if (coll->th.start_t < 0)
	{
		write_stderr("Failed to get the start_time");
		return (-5);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_coll	coll;

	if (!check_input(argc, argv, &coll.in))
		return (1);
	if (!coll_init(&coll))
		return (free_memory(&coll), 1);
	if (print_thread(&coll) < 0)
		return (free_memory(&coll), 1);
	if (pthread_join(coll.th.monitor, NULL) != 0)
	{
		write_stderr("Failed to join the monitor thread.\n");
		return (free_memory(&coll), 1);
	}
	if (coll.th.exit_status != 0)
	{
		write_stderr("\033[1;31mProblem occur in monitor thread.\033[0m\n");
		printf("\033[1;31mThe monitor thread return"
			" value: %d\033[0m\n", coll.th.exit_status);
	}
	if (!join_philo_threads(&coll.th, coll.ph, coll.in.philo_num))
		return (free_memory(&coll), 1);
	free_memory(&coll);
	return (0);
}
