/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarkas <tfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:18:06 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/07 21:16:49 by tfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

static int	check_argnum(int argc)
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

static int	ft_atoi_p(const char *str)
{
	unsigned long long	num;
	int					i;

	num = 0;
	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '0')
		return (-2);
	while (str[i] && ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-3);
	else if (num > 2147483647)
		return (-4);
	return (num);
}

static void	ch_argv_msg(int err_status)
{
	if (err_status == -1)
		write_stderr("\033[1;31mThe input NULL in ft_atoi_p.\033[0m\n");
	else if (err_status == -2)
		write_stderr("\033[1;31mThe input should be pozitive number.\033[0m\n");
	else if (err_status == -3)
		write_stderr("\033[1;31mThe input should includes"
			" just digits.\033[0m\n");
	else if (err_status == -4)
		write_stderr("\033[1;31mThe input should be less than"
			" int MAX = 2147483647.\033[0m\n");
}

static int	check_argval(int argc, char **argv, t_input *in_args)
{
	int	i;
	int	input_num;

	i = 1;
	while (i < argc)
	{
		input_num = ft_atoi_p(argv[i]);
		if (input_num < 0)
			return (input_num);
		store_input(input_num, in_args);
		i++;
	}
	return (1);
}

int	check_input(int argc, char **argv, t_input *in_args)
{
	int	check;

	if (!check_argnum(argc))
		return (0);
	check = check_argval(argc, argv, in_args);
	if (check < 0)
	{
		ch_argv_msg(check);
		return (0);
	}
	return (1);
}
