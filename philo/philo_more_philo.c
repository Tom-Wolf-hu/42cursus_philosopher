/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_more_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarkas <tfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:43:37 by tamas             #+#    #+#             */
/*   Updated: 2025/05/20 13:39:48 by tfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

static int	check_meal_count(t_coll *coll)
{
	int	result;

	result = 0;
	if (pthread_mutex_lock(&coll->eat_count) != 0)
	{
		write_stderr("Failed to lock eat_count mutex.\n");
		return (-1);
	}
	if (coll->th.count_enough_eat == coll->in.philo_num)
	{
		if (change_sim_end(coll) < 0)
			result = 1;
		printf("\033[1;32mAll philosophers eat at"
			" least %d times.\033[0m\n", coll->in.eat_num);
		result = 1;
	}
	if (pthread_mutex_unlock(&coll->eat_count) != 0)
	{
		write_stderr("Failed to unlock eat_count mutex.\n");
		return (-1);
	}
	return (result);
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
			print_message(curren_t - coll->th.start_t,
				coll->ph[i]->philo_id, DIE);
			return (1);
		}
	}
	return (0);
}

static int	check_das_while(t_coll *coll, long curren_t, int i)
{
	if (pthread_mutex_lock(&coll->modify_state) != 0)
	{
		write_stderr("Failed to lock modify_state mutex.\n");
		return (1);
	}
	if (check_die(coll, curren_t, i))
	{
		if (pthread_mutex_unlock(&coll->modify_state) != 0)
		{
			write_stderr("Failed to unlock modify_state mutex.\n");
		}
		return (1);
	}
	check_state(coll, curren_t, i);
	if (pthread_mutex_unlock(&coll->modify_state) != 0)
	{
		write_stderr("Failed to unlock modify_state mutex.\n");
		return (1);
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
		if (check_das_while(coll, curren_t, i) == 1)
			return (1);
	}
	return (0);
}

/*
	In the while cycle previously I used usleep(200).
	However when I had to modify the check_die_and_state function
	the reason of data race, with 200 number philos doesn't work anymore.
*/
int	more_philo(t_coll *coll)
{
	int	check_die;
	int	check_meal;	

	check_meal = 0;
	while (!coll->th.sim_end)
	{
		check_die = check_die_and_state(coll);
		if (coll->in.eat_num != -1)
			check_meal = check_meal_count(coll);
		if (check_die == 1 || check_meal == 1)
			return (1);
		else if (check_die < 0 || check_meal < 0)
		{
			write_stderr("Error in check_die or check_meal_count.\n");
			return (-1);
		}
	}
	return (0);
}
