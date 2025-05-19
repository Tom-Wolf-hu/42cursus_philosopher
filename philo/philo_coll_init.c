/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_coll_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:55:05 by tamas             #+#    #+#             */
/*   Updated: 2025/05/19 10:56:38 by tamas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

static int	coll_ph_allocate(t_coll *coll)
{
	int	i;

	i = 0;
	coll->ph = (t_philo **)malloc(coll->in.philo_num * sizeof(t_philo *));
	if (!coll->ph)
	{
		write_stderr("Failed to allocate memory for ph philo double pointer\n");
		return (-1);
	}
	while (i < coll->in.philo_num)
	{
		coll->ph[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!coll->ph[i])
		{
			write_stderr("Failed allocate memory for individual philo.\n");
			while (--i >= 0)
				free(coll->ph[i]);
			free(coll->ph);
			coll->ph = NULL;
			return (-2);
		}
		i++;
	}
	return (0);
}

static void	coll_ph_init(t_coll *coll)
{
	int	i;

	i = -1;
	while (++i < coll->in.philo_num)
	{
		coll->ph[i]->philo_id = i + 1;
		coll->ph[i]->eat_start_t = -1;
		coll->ph[i]->eat_time = (long)coll->in.eat_t;
		coll->ph[i]->sleep_time = (long)coll->in.sleep_t;
		coll->ph[i]->state_changed = 0;
		coll->ph[i]->thinked = 0;
		coll->ph[i]->num_fork = 0;
		coll->ph[i]->meal_count = 0;
		if (coll->in.eat_num == -1)
			coll->ph[i]->meal_count = -1;
		coll->ph[i]->right_fork = NULL;
		if (i == 0 && coll->in.philo_num > 1)
			coll->ph[i]->right_fork = &coll->fork[coll->in.philo_num - 1];
		else if (i > 0)
			coll->ph[i]->right_fork = &coll->fork[i - 1];
		coll->ph[i]->left_fork = &coll->fork[i];
		coll->ph[i]->sim_end = &coll->th.sim_end;
		coll->ph[i]->finish = &coll->finish;
		coll->ph[i]->modify_state = &coll->modify_state;
	}
}

int	coll_init(t_coll *coll)
{
	coll->th.philo = NULL;
	coll->th.start_t = -1;
	coll->th.sim_end = 0;
	if (create_control_mutexes(coll) < 0)
		return (0);
	if (create_fork_mutexes(coll) < 0)
		return (0);
	if (coll_ph_allocate(coll) < 0)
		return (0);
	coll_ph_init(coll);
	return (1);
}
