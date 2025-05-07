/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarkas <tfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:02:05 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/07 20:27:12 by tfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	main(int argc, char **argv)
{
	if (!check_input(argc, argv))
		return (1);
	printf("This is argv: %s\n", argv[1]);
	return (0);
}