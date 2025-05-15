/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:43:37 by tamas             #+#    #+#             */
/*   Updated: 2025/05/15 16:01:32 by tamas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	more_philo(t_coll *coll)
{
	int	every_body_eat_enough;
	
	every_body_eat_enough = 0;
	while(!coll->ph.smb_died && !every_body_eat_enough)
	{
		//philo_loop with check die time function
		if (coll->in.eat_num != -1 && coll->ph.meal_count == coll->in.eat_num)
			//philo_loop with check meal count
		//philo_loop with check if philo state changed
		usleep(200);
	}
	return (0);
}

int	check_die(t_coll *coll)
{
	int	i;
	long	curren_t;
	
	i = 0;
	curren_t = get_current_time();
	if (curren_t == -1)
		return (curren_t);
	while (i < coll->in.philo_num)
	{
		if (coll->ph[i].eat_start_t == -1)
		{
			if (curren_t - coll->th.start_t > coll->in.die_t)
			{
				died_func(coll->ph, (long)coll->in.die_t, coll->th.start_t);
				return (1);
			}
		}
		else
		{
			if (curren_t - coll->ph[i].eat_start_t > coll->in.die_t)
			{
				died_func(coll->ph, (long)coll->in.die_t, coll->ph[i].eat_start_t);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
