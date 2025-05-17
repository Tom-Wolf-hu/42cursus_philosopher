/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_store.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:14:37 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/17 10:53:22 by tamas            ###   ########.fr       */
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

int	create_control_mutex(t_coll *coll)
{
	if (pthread_mutex_init(&coll->control, NULL) != 0)
	{
		write_stderr("The control mutex initialization failed.\n");
		return (-1);
	}
	return (0);
}

int	coll_init(t_coll *coll)
{
	int	i;
	
	i = 0;
	coll->th.philo = NULL;
	coll->th.start_t = -1;
	coll->fork = NULL;
	coll->ph = (t_philo **)malloc(coll->in.philo_num * sizeof(t_philo *));
	if (!coll->ph)
	{
		write_stderr("Failed to allocate memory for ph philo double pointer\n");
		return (0);
	}
	while (i < coll->in.philo_num)
	{
		coll->ph[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!coll->ph[i])
		{
			write_stderr("Failed allocate memory for idividual philo.\n");
			while(--i >= 0)
				free(coll->ph[i]);
			free(coll->ph);
			coll->ph = NULL;
			return (0);
		}
		coll->ph[i]->philo_id = i + 1;
		coll->ph[i]->eat_start_t = -1;
		coll->ph[i]->state_changed = 0;
		coll->ph[i]->num_fork = 0;
		coll->ph[i]->meal_count = 0;
		coll->ph[i]->smb_died = 0;
		i++;
	}
	return (1);
}
