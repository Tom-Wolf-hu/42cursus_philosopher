/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:43:37 by tamas             #+#    #+#             */
/*   Updated: 2025/05/15 01:08:48 by tamas            ###   ########.fr       */
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