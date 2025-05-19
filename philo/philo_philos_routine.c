/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_philos_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:39:13 by tamas             #+#    #+#             */
/*   Updated: 2025/05/19 13:39:21 by tamas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	change_philo_state(t_philo *ph, t_state ch_state)
{
	if (pthread_mutex_lock(ph->modify_state) != 0)
	{
		write_stderr("Failed to lock the modify state.\n");
		return (-1);
	}
	ph->st = ch_state;
	ph->state_changed = 1;
	if (pthread_mutex_unlock(ph->modify_state) != 0)
	{
		write_stderr("Failed to unlock the modify state.\n");
		return (-2);
	}
	return (0);
}

static int	lock_fork(t_philo *ph, pthread_mutex_t *first_fork,
	pthread_mutex_t *second_fork)
{
	if (pthread_mutex_lock(first_fork) != 0)
	{
		write_stderr("Failed to lock the first fork.\n");
		return (-1);
	}
	if (change_philo_state(ph, FORK) < 0)
		return (-2);
	if (pthread_mutex_lock(second_fork) != 0)
	{
		write_stderr("Failed to lock the second fork.\n");
		return (-3);
	}
	return (0);
}

static int	eat_procedure(t_philo *ph)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = ph->right_fork;
	second_fork = ph->left_fork;
	if (ph->philo_id % 2 == 1)
	{
		first_fork = ph->left_fork;
		second_fork = ph->right_fork;
	}
	if (lock_fork(ph, first_fork, second_fork) < 0)
		return (-1);
	if (eat_func(ph) < 0)
		return (-4);
	if (pthread_mutex_unlock(second_fork) != 0)
	{
		write_stderr("Failed to unlock the second fork.\n");
		return (-5);
	}
	if (pthread_mutex_unlock(first_fork) != 0)
	{
		write_stderr("Failed to unlock the first fork.\n");
		return (-6);
	}
	return (0);
}

static int	do_eat_sleep_think(t_philo *ph)
{
	while (!(*(ph->sim_end)))
	{
		if (pthread_mutex_unlock(ph->finish) != 0)
		{
			write_stderr("Failed to unlock finish mutex in more_philo.\n");
			return (-1);
		}
		if (eat_procedure(ph) < 0)
			return (-2);
		if (sleep_func(ph) < 0)
			return (-3);
		if (change_philo_state(ph, THINK) < 0)
			return (-1);
		if (pthread_mutex_lock(ph->finish) != 0)
		{
			write_stderr("Failed to lock finish mutex in more_philo.\n");
			return (-1);
		}
	}
	return (0);
}

void	*philos_routine(void *arg)
{
	t_philo	*ph;

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
	if (do_eat_sleep_think(ph) < 0)
		return ((void *)2);
	if (pthread_mutex_unlock(ph->finish) != 0)
	{
		write_stderr("Failed to unlock finish mutex in more_philo.\n");
		return ((void *)3);
	}
	return ((void *)0);
}
