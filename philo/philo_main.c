/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:02:05 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/18 15:46:06 by tamas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	*philos_routine(void *arg)
{
	t_philo	*ph;
	int 	i;

	i = 0;
	ph = (t_philo *)arg;
	if (ph->philo_id % 2 == 1)
		usleep(100);
	if (!ph->right_fork)
		return ((void *)0);
	if (pthread_mutex_lock(ph->finish) != 0)
	{
		write_stderr("Failed to lock finish mutex in more_philo.\n");
		return ((void *)1);
	}
	while (!(*(ph->sim_end)))
	{
		i++;
		if (i < 9)
			printf("\033[1;35m[%d] The philo_id: %d The ph->sim_end: %d\033[0m\n", i, ph->philo_id, *(ph->sim_end));
		if (pthread_mutex_unlock(ph->finish) != 0)
		{
			write_stderr("Failed to unlock finish mutex in more_philo.\n");
			return ((void *)1);
		}
		if (ph->philo_id % 2 == 1)
		{
			if (pthread_mutex_lock(ph->left_fork) != 0)
			{
				write_stderr("Failed to lock the left fork.\n");
				return ((void *)1);
			}
			if (pthread_mutex_lock(ph->modify_state) != 0)
			{
				write_stderr("Failed to lock the modify state.\n");
				return ((void *)1);
			}
			ph->st = FORK;
			ph->state_changed = 1;
			if (pthread_mutex_unlock(ph->modify_state) != 0)
			{
				write_stderr("Failed to unlock the modify state.\n");
				return ((void *)1);
			}
			if (pthread_mutex_lock(ph->right_fork) != 0)
			{
				write_stderr("Failed to lock the right fork.\n");
				return ((void *)1);
			}
		}
		else
		{
			if (pthread_mutex_lock(ph->right_fork) != 0)
			{
				write_stderr("Failed to lock the left fork.\n");
				return ((void *)1);
			}
			if (pthread_mutex_lock(ph->modify_state) != 0)
			{
				write_stderr("Failed to lock the modify state.\n");
				return ((void *)1);
			}
			ph->st = FORK;
			ph->state_changed = 1;
			if (pthread_mutex_unlock(ph->modify_state) != 0)
			{
				write_stderr("Failed to unlock the modify state.\n");
				return ((void *)1);
			}
			if (pthread_mutex_lock(ph->left_fork) != 0)
			{
				write_stderr("Failed to lock the right fork.\n");
				return ((void *)1);
			}
		}
		if (eat_func(ph) < 0)
			return ((void *)2);
		// printf("The philo[%d] are saying hello to you.\n", ph->philo_id);
		if (ph->philo_id % 2 == 1)
		{
			if (pthread_mutex_unlock(ph->left_fork) != 0)
			{
				write_stderr("Failed to unlock the left fork.\n");
				return ((void *)1);
			}
			if (pthread_mutex_unlock(ph->right_fork) != 0)
			{
				write_stderr("Failed to unlock the right fork.\n");
				return ((void *)1);
			}
		}
		else
		{
			if (pthread_mutex_unlock(ph->right_fork) != 0)
			{
				write_stderr("Failed to unlock the left fork.\n");
				return ((void *)1);
			}
			if (pthread_mutex_unlock(ph->left_fork) != 0)
			{
				write_stderr("Failed to unlock the right fork.\n");
				return ((void *)1);
			}
		}
		if (sleep_func(ph) < 0)
			return ((void *)3);
		if (pthread_mutex_lock(ph->modify_state) != 0)
		{
			write_stderr("Failed to lock the modify state.\n");
			return ((void *)1);
		}
		ph->st = THINK;
		ph->state_changed = 1;
		if (pthread_mutex_unlock(ph->modify_state) != 0)
		{
			write_stderr("Failed to unlock the modify state.\n");
			return ((void *)1);
		}
		if (i < 9)
			printf("\033[1;32m[%d] The philo_id: %d The ph->sim_end: %d\033[0m\n", i, ph->philo_id, *(ph->sim_end));
		if (pthread_mutex_lock(ph->finish) != 0)
		{
			write_stderr("Failed to lock finish mutex in more_philo.\n");
			return ((void *)1);
		}
	}
	if (pthread_mutex_unlock(ph->finish) != 0)
	{
		write_stderr("Failed to unlock finish mutex in more_philo.\n");
		return ((void *)1);
	}
	return ((void *)0);
}

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
		// if (pthread_create(&(coll->th.philo[i]), NULL, testfunc, NULL) != 0)
		// {
		// 	write_stderr("philo thread creation failed.\n");
		// 	return (free_memory(&coll->th), -2);
		// }
		i++;
	}
	return (0);
}

void	*print_monitor(void *arg)
{
	t_coll	*coll;
	int		i;

	i = 0;
	coll = (t_coll *)arg;
	while (coll->th.start_t < 0)
	{
		usleep(10);
		continue ;
	}
	while (i < coll->in.philo_num)
	{
		print_message(get_current_time() - coll->th.start_t, i + 1, THINK);
		i++;
	}
	if (coll->in.philo_num == 1)
	{
		if (one_philo(coll->th.start_t, (long)coll->in.die_t) < 0)
			return((void *)1);
	}
	else
	{
		if (more_philo(coll) < 0)
			return((void *)2);
	}
	return((void *)0);
}

int	print_thread(t_coll *coll)
{
	if (pthread_create(&(coll->th.monitor), NULL, print_monitor, (void *)coll) != 0)
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

	// pthread_create(&id, NULL, testfunc, NULL);
	write(1, "passed0\n", 8);
	if (!check_input(argc, argv, &coll.in))
		return (1);
	write(1, "passed1\n", 8);
	if (!coll_init(&coll))
		return (1);
	write(1, "passed2\n", 8);
	if (!coll.fork)
		printf("\033[1,33mthe coll fork NULL before print_thread\n\033m");
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
	// main_thread_print(&coll);
	free_memory(&coll);
	return (0);
}
