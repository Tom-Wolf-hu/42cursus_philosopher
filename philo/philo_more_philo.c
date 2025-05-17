/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_more_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:43:37 by tamas             #+#    #+#             */
/*   Updated: 2025/05/17 10:36:06 by tamas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

static int	check_meal_count(t_coll *coll, int *eat_enough)
{
	int count;
	int	i;

	count = 0;
	i = 0;
	while (i < coll->in.philo_num)
	{
		if (coll->ph[i].meal_count == coll->in.eat_num)
			count++;
		i++;
	}
	if (count == coll->in.philo_num)
	{
		*eat_enough = 1;
		printf("\033[1;32mAll philosophers eat at"
			" least %d times.\033[0m\n", coll->in.philo_num);
		return (1);
	}
	return (0);
}

static int	check_die(t_coll *coll, long curren_t, int i)
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
	return (0);
}

static void	check_state(t_coll *coll, long curren_t, int i)
{
	if (!coll->ph[i].state_changed)
		return ;
	if (coll->ph[i].st == FORK)
		print_message(curren_t - coll->th.start_t, coll->ph[i].pilo_id, FORK);
	if (coll->ph[i].st == EAT)
	{
		if (coll->ph[i].num_fork == 0)
			print_message(curren_t - coll->th.start_t, coll->ph[i].pilo_id, FORK);
		print_message(curren_t - coll->th.start_t, coll->ph[i].pilo_id, FORK);
		print_message(curren_t - coll->th.start_t, coll->ph[i].pilo_id, EAT);
	}
	if (coll->ph[i].st == SLEEP)
		print_message(curren_t - coll->th.start_t, coll->ph[i].pilo_id, SLEEP);
	if (coll->ph[i].st == THINK)
		print_message(curren_t - coll->th.start_t, coll->ph[i].pilo_id, THINK);
	coll->ph[i].state_changed = 0;
}

static int	check_die_and_state(t_coll *coll)
{
	int	i;
	long	curren_t;
	
	i = 0;
	curren_t = get_current_time();
	if (curren_t == -1)
		return (curren_t);
	while (i < coll->in.philo_num)
	{
		if (check_die(coll, curren_t, i))
			return (1);
		check_state(coll, curren_t, i);
		i++;
	}
	return (0);
}

int	more_philo(t_coll *coll_orig)
{
	int		every_body_eat_enough;
	t_coll	*coll;
	
	every_body_eat_enough = 0;
	while(!coll->ph.smb_died && !every_body_eat_enough)
	{
		if (pthread_mutex_lock(&coll_orig->control) != 0)
		{
			write_stderr("Failed to lock control mutex in more_philo.\n");
			return (1);
		}
		coll = coll_orig;
		if (pthread_mutex_unlock(&coll_orig->control) != 0)
		{
			write_stderr("Failed to unlock control mutex in more_philo.\n");
			return (1);
		}
		if (check_die_and_state(coll))
			return (1);
		if (coll->in.eat_num != -1 && coll->ph.meal_count == coll->in.eat_num)
			if (check_meal_count(coll, &eat_enough))
				return (1);
		if (pthread_mutex_lock(&coll_orig->control) != 0)
		{
			write_stderr("Failed to lock control mutex in more_philo.\n");
			return (1);
		}
		coll_orig-> = coll_orig;
		if (pthread_mutex_unlock(&coll_orig->control) != 0)
		{
			write_stderr("Failed to unlock control mutex in more_philo.\n");
			return (1);
		}
		usleep(200);
	}
	return (0);
}
