/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarkas <tfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:04:17 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/10 16:11:44 by tfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HEADER_H
# define PHILO_HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
}	t_state;

typedef struct s_input
{
	int	philo_num;
	int	die_t;
	int	eat_t;
	int	sleep_t;
	int	eat_num;
}	t_input;

//This structure consists dynamically allocated memory: philo, fork
typedef struct s_thread
{
	long			start_t;
	pthread_t		*philo;
	pthread_t		monitor;
	pthread_mutex_t	*fork;
}	t_thread;

typedef struct s_philo
{
	int		philo_id;
	long	eat_start_t;
	int		num_fork;
	t_state	st;
}	t_philo;

typedef	struct s_coll
{
	t_input		in;
	t_thread	th;
	t_philo		ph;
}	t_coll;


//philo_utils.c
int		ft_strlen_p(char *str);
void	write_stderr(char *str);
int		ft_isspace(char ch);
int		ft_isdigit(char ch);

//philo_check_input.c
int		check_input(int argc, char **argv, t_input *in_args);

//philo_store.c
void	store_input(int input_num, t_input *in_args);

#endif