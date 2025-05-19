/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:04:17 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/19 23:59:22 by tamas            ###   ########.fr       */
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

//This structure consists dynamically allocated memory: philo
typedef struct s_thread
{
	long			start_t;
	pthread_t		*philo;
	pthread_t		monitor;
	int				sim_end;
	int				count_enough_eat;
}	t_thread;

typedef struct s_philo
{
	int				philo_id;
	long			eat_start_t;
	long			eat_time;
	long			sleep_time;
	int				state_changed;
	int				thinked;
	int				num_fork;
	int				meal_count;
	int				eat_num;
	int				*sim_end;
	int				*count_enough_eat;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*finish;
	pthread_mutex_t	*eat_count;
	pthread_mutex_t	*modify_state;
	t_state			st;
}	t_philo;

//This structure consists dynamically allocated memory: fork, ph
typedef struct s_coll
{
	t_input			in;
	t_thread		th;
	t_philo			**ph;
	pthread_mutex_t	start;
	pthread_mutex_t	finish;
	pthread_mutex_t	eat_count;
	pthread_mutex_t	modify_state;
	pthread_mutex_t	*fork;
}	t_coll;

//philo_message.c
int		one_philo(long start_t, long die_t);
void	print_message(long time_ms, int philo_num, t_state message);

//philo_utils.c
int		ft_strlen_p(char *str);
void	write_stderr(char *str);
int		ft_isspace(char ch);
int		ft_isdigit(char ch);

//philo_time.c
long	get_current_time(void);
long	my_usleep(long sleep_time_ms);

//philo_check_input.c
int		check_input(int argc, char **argv, t_input *in_args);

//philo_store.c
void	store_input(int input_num, t_input *in_args);
int		create_control_mutexes(t_coll *coll);
int		create_fork_mutexes(t_coll *coll);

//philo_coll_init.c
int		coll_init(t_coll *coll);

//philo_philos_routine.c
int		change_philo_state(t_philo *ph, t_state ch_state);
void	*philos_routine(void *arg);

//philo_action.c
int		sleep_func(t_philo *ph);
int		eat_func(t_philo *ph);

//philo_more_philo.c
int		more_philo(t_coll *coll_orig);

//philo_check_state.c
void	check_state(t_coll *coll, long curren_t, int i);

//philo_close.c
int		join_philo_threads(t_thread *th, int num_threads);
void	destroy_mutexes(t_coll *coll);
void	free_memory(t_coll *coll);

#endif