/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarkas <tfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:02:05 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/07 15:39:07 by tfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	ft_strlen_p(char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
		return (-1);
	while (str[len] != '\0')
		len++;
	return (len);
}

void	write_stderr(char *str)
{
	int	strlen;

	strlen = ft_strlen_p(str);
	if (strlen == -1 || strlen == 0)
		write(2, "Error\n", 6);
	else
		write(2, str, strlen);
}

int	check_argnum(int argc)
{
	if (argc < 5 || argc > 6)
	{
		write_stderr("Please give the input argument for "
			"the program the following way:\n");
		write_stderr("\033[1;33m\nnumber_of_pfilosophers time_to_die"
			" time_to_eat time_to_eat time_to_sleep"
			" [number_of_times_each_philosopher_must_eat]\n\n\033[0m");
		write_stderr("The last parameter optional.\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	if (!check_argnum(argc))
		return (1);
	printf("This is argv: %s\n", argv[1]);
	return (0);
}