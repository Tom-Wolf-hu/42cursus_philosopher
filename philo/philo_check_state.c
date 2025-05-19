/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:22:42 by tamas             #+#    #+#             */
/*   Updated: 2025/05/19 11:24:38 by tamas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	check_state(t_coll *coll, long curren_t, int i)
{
	if (!coll->ph[i]->state_changed)
		return ;
	if (coll->ph[i]->thinked != 1)
	{
		coll->ph[i]->thinked = 1;
		print_message(curren_t - coll->th.start_t,
			coll->ph[i]->philo_id, THINK);
	}
	if (coll->ph[i]->st == FORK)
		print_message(curren_t - coll->th.start_t,
			coll->ph[i]->philo_id, FORK);
	if (coll->ph[i]->st == EAT)
	{
		if (coll->ph[i]->thinked != 1)
			print_message(curren_t - coll->th.start_t,
				coll->ph[i]->philo_id, THINK);
		if (coll->ph[i]->num_fork == 0)
			print_message(curren_t - coll->th.start_t,
				coll->ph[i]->philo_id, FORK);
		print_message(curren_t - coll->th.start_t, coll->ph[i]->philo_id, FORK);
		print_message(curren_t - coll->th.start_t, coll->ph[i]->philo_id, EAT);
		coll->ph[i]->thinked = 0;
	}
	if (coll->ph[i]->st == SLEEP)
		print_message(curren_t - coll->th.start_t,
			coll->ph[i]->philo_id, SLEEP);
	if (coll->ph[i]->st == THINK)
	{
		coll->ph[i]->thinked = 1;
		print_message(curren_t - coll->th.start_t,
			coll->ph[i]->philo_id, THINK);
	}
	coll->ph[i]->state_changed = 0;
}
