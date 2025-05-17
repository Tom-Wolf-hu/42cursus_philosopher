/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:52:46 by tamas             #+#    #+#             */
/*   Updated: 2025/05/17 11:05:43 by tamas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	join_philo_threads(t_thread *th, int num_threads)
{
	int	i;

	i = 0;
	while (i < num_threads)
	{
		if (pthread_join(th->philo[i], NULL) != 0)
		{
			write_stderr("Failed to join philo thread.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	free_memory(t_coll *coll)
{
	int	i;

	i = 0;
	// Destroy the control mutex if it was initialized
	if (coll->in.philo_num > 0 && pthread_mutex_destroy(&coll->control) != 0)
		write_stderr("Failed to destroy the control mutex.\n");

	// Destroy fork mutexes if they were initialized
	if (coll->fork != NULL)
	{
		while (i < coll->in.philo_num)
		{
			if (pthread_mutex_destroy(&coll->fork[i]) != 0)
				write_stderr("Failed to destroy the fork mutex.\n");
			i++;
		}
		free(coll->fork);
		coll->fork = NULL;
	}

	i = 0;
	if (coll->ph)
	{
		while (i < coll->in.philo_num)
		{
			free(coll->ph[i]);
			i++;
		}
		free(coll->ph);
		coll->ph = NULL;
	}

	// Free philosopher threads if allocated
	if (coll->th.philo != NULL)
	{
		free(coll->th.philo);
		coll->th.philo = NULL;
	}
}
