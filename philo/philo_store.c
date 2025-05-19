/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_store.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:14:37 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/19 10:56:31 by tamas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	store_input(int input_num, t_input *in_args)
{
	static int	count = 0;

	in_args->eat_num = -1;
	if (count == 0)
		in_args->philo_num = input_num;
	else if (count == 1)
		in_args->die_t = input_num;
	else if (count == 2)
		in_args->eat_t = input_num;
	else if (count == 3)
		in_args->sleep_t = input_num;
	else if (count == 4)
		in_args->eat_num = input_num;
	count++;
}

int	create_fork_mutexes(t_coll *coll)
{
	int	i;

	i = 0;
	coll->fork = malloc(coll->in.philo_num * sizeof(pthread_mutex_t));
	if (!coll->fork)
	{
		write_stderr("Failed to allocate memory for fork mutexes.\n");
		return (-1);
	}
	while (i < coll->in.philo_num)
	{
		if (pthread_mutex_init(&coll->fork[i], NULL) != 0)
		{
			write_stderr("Failed to initialize a fork mutex.\n");
			while (--i >= 0)
				pthread_mutex_destroy(&coll->fork[i]);
			free(coll->fork);
			coll->fork = NULL;
			return (-2);
		}
		i++;
	}
	return (0);
}

int	create_control_mutexes(t_coll *coll)
{
	if (pthread_mutex_init(&coll->finish, NULL) != 0)
	{
		write_stderr("The finish mutex initialization failed.\n");
		return (-1);
	}
	if (pthread_mutex_init(&coll->modify_state, NULL) != 0)
	{
		write_stderr("The modify_state mutex initialization failed.\n");
		return (-2);
	}
	return (0);
}
