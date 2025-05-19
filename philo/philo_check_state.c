/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:22:42 by tamas             #+#    #+#             */
/*   Updated: 2025/05/19 14:41:15 by tamas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

static void	check_fork(t_coll *coll, long curren_t, int i)
{
	if (coll->ph[i]->st == FORK)
	{
		if (coll->ph[i]->thinked != 1)
		{
			coll->ph[i]->thinked = 1;
			printf("\033[1;31mbefore fork: ");
			print_message(curren_t - coll->th.start_t,
				coll->ph[i]->philo_id, THINK);
			printf("\033[0m");
		}
		print_message(curren_t - coll->th.start_t,
			coll->ph[i]->philo_id, FORK);
	}
}

static void	check_eat(t_coll *coll, long curren_t, int i)
{
	if (coll->ph[i]->st == EAT)
	{
		if (coll->ph[i]->thinked != 1)
		{
			printf("\033[1;33mbefore eat: ");
			print_message(curren_t - coll->th.start_t,
				coll->ph[i]->philo_id, THINK);
			printf("\033[0m");
		}
		if (coll->ph[i]->num_fork == 0)
			print_message(curren_t - coll->th.start_t,
				coll->ph[i]->philo_id, FORK);
		print_message(curren_t - coll->th.start_t, coll->ph[i]->philo_id, FORK);
		print_message(curren_t - coll->th.start_t, coll->ph[i]->philo_id, EAT);
		coll->ph[i]->thinked = 0;
	}
}

void	check_state(t_coll *coll, long curren_t, int i)
{
	if (!coll->ph[i]->state_changed)
		return ;
	check_fork(coll, curren_t, i);
	check_eat(coll, curren_t, i);
	if (coll->ph[i]->st == SLEEP)
		print_message(curren_t - coll->th.start_t,
			coll->ph[i]->philo_id, SLEEP);
	if (coll->ph[i]->st == THINK)
	{
		coll->ph[i]->thinked = 1;
		printf("\033[1;35mafter sleep: ");
		print_message(curren_t - coll->th.start_t,
			coll->ph[i]->philo_id, THINK);
		printf("\033[0m");
	}
	coll->ph[i]->state_changed = 0;
}
