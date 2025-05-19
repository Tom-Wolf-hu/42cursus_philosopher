/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:11:33 by tamas             #+#    #+#             */
/*   Updated: 2025/05/19 09:59:14 by tamas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	sleep_func(t_philo *ph)
{
	if (pthread_mutex_lock(ph->modify_state) != 0)
	{
		write_stderr("Failed to lock the modify state.\n");
		return (-1);
	}
	ph->st = SLEEP;
	ph->state_changed = 1;
	if (pthread_mutex_unlock(ph->modify_state) != 0)
	{
		write_stderr("Failed to unlock the modify state.\n");
		return (-2);
	}
	if (my_usleep(ph->sleep_time) == -1)
	{
		write_stderr("\033[1;31mPhilosopher can't sleep enough time\033[0m\n");
		return (-3);
	}
	return (0);
}

int	eat_func(t_philo *ph)
{
	if (pthread_mutex_lock(ph->modify_state) != 0)
	{
		write_stderr("Failed to lock the modify state.\n");
		return (-1);
	}
	ph->eat_start_t = get_current_time();
	if (ph->eat_start_t == -1)
		return (-2);
	ph->st = EAT;
	ph->state_changed = 1;
	if (pthread_mutex_unlock(ph->modify_state) != 0)
	{
		write_stderr("Failed to unlock the modify state.\n");
		return (-3);
	}
	if (my_usleep(ph->eat_time) == -1)
	{
		write_stderr("\033[1;31mPhilosopher can't eat enough time\033[0m\n");
		return (-4);
	}
	if (ph->meal_count != -1)
		ph->meal_count++;
	return (0);
}
