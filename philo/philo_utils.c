/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:13:14 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/16 12:53:25 by tamas            ###   ########.fr       */
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

int	ft_isspace(char ch)
{
	if (ch == '\t' || ch == '\r' || ch == '\n'
		|| ch == ' ' || ch == '\v' || ch == '\f')
	{
		return (1);
	}
	return (0);
}

int	ft_isdigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
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

	// Free philosopher threads if allocated
	if (coll->th.philo != NULL)
	{
		free(coll->th.philo);
		coll->th.philo = NULL;
	}
}
