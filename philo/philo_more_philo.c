/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_more_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:43:37 by tamas             #+#    #+#             */
/*   Updated: 2025/05/19 11:23:42 by tamas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

static int	change_sim_end(t_coll *coll)
{
	if (pthread_mutex_lock(&coll->finish) != 0)
	{
		write_stderr("Failed to lock finish mutex.\n");
		return (-1);
	}
	coll->th.sim_end = 1;
	if (pthread_mutex_unlock(&coll->finish) != 0)
	{
		write_stderr("Failed to unlock finish mutex.\n");
		return (-1);
	}
	return (0);
}

static int	check_meal_count(t_coll *coll)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < coll->in.philo_num)
	{
		if (coll->ph[i]->meal_count == coll->in.eat_num)
			count++;
		i++;
	}
	if (count == coll->in.philo_num)
	{
		if (change_sim_end(coll) < 0)
			return (1);
		printf("\033[1;32mAll philosophers eat at"
			" least %d times.\033[0m\n", coll->in.eat_num);
		return (1);
	}
	return (0);
}

static int	check_die(t_coll *coll, long curren_t, int i)
{
	if (coll->ph[i]->eat_start_t == -1)
	{
		if (curren_t - coll->th.start_t > coll->in.die_t)
		{
			if (change_sim_end(coll) < 0)
				return (1);
			print_message(curren_t - coll->th.start_t,
				coll->ph[i]->philo_id, DIE);
			return (1);
		}
	}
	else
	{
		if (curren_t - coll->ph[i]->eat_start_t > coll->in.die_t)
		{
			if (change_sim_end(coll) < 0)
				return (1);
			print_message(curren_t - coll->ph[i]->eat_start_t,
				coll->ph[i]->philo_id, DIE);
			return (1);
		}
	}
	return (0);
}

static int	check_die_and_state(t_coll *coll)
{
	int		i;
	long	curren_t;

	i = -1;
	curren_t = get_current_time();
	if (curren_t == -1)
		return (curren_t);
	while (++i < coll->in.philo_num)
	{
		if (check_die(coll, curren_t, i))
			return (1);
		if (pthread_mutex_lock(&coll->modify_state) != 0)
		{
			write_stderr("Failed to lock modify_state mutex in check_state.\n");
			return (1);
		}
		check_state(coll, curren_t, i);
		if (pthread_mutex_unlock(&coll->modify_state) != 0)
		{
			write_stderr("Failed to unlock modify_state"
				" mutex in check_state.\n");
			return (1);
		}
	}
	return (0);
}

int	more_philo(t_coll *coll)
{
	while (!coll->th.sim_end)
	{
		if (check_die_and_state(coll))
			return (-1);
		if (coll->in.eat_num != -1)
			if (check_meal_count(coll))
				return (-2);
		usleep(200);
	}
	return (0);
}
