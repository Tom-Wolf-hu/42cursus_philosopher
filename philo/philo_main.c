/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarkas <tfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:02:05 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/07 14:24:45 by tfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		printf("\033[1;33mThis is the message.\033[0m\n");
		write(2, "hello\n", 5);
	}
	else if (argc > 1)
	{
		printf("This is argv: %s\n", argv[1]);
	}
	return (0);
}