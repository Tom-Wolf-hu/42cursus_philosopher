/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_store.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:14:37 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/16 14:13:19 by tamas            ###   ########.fr       */
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

int	coll_init(t_coll *coll)
{
	int	i;
	
	i = 0;
	coll->th.philo = NULL;
	coll->th.start_t = -1;
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
