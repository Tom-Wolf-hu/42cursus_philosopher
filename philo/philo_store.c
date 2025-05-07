/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_store.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarkas <tfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:14:37 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/07 21:15:42 by tfarkas          ###   ########.fr       */
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
