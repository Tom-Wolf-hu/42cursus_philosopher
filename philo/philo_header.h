/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarkas <tfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:04:17 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/07 20:25:42 by tfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HEADER_H
# define PHILO_HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

//philo_utils.c
int		ft_strlen_p(char *str);
void	write_stderr(char *str);
int		ft_isspace(char ch);
int		ft_isdigit(char ch);

//philo_check_input.c
int		check_input(int argc, char **argv);

#endif