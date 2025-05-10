/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarkas <tfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:02:05 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/10 14:00:59 by tfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

long	get_current_time(void)
{
	struct timeval	current;
	long			time_in_ms;

	if (gettimeofday(&current, NULL) == -1)
	{
		write_stderr("Get the current time function Failed.\n");
		return (-1);
	}
	time_in_ms = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (time_in_ms);
}

long	my_usleep(long sleep_time_ms)
{
	long	start_sleep;
	long	end_sleep;

	start_sleep = get_current_time();
	if (sleep_time_ms > 10)
		usleep(sleep_time_ms * 1000 - 10000);
	while (1)
	{
		end_sleep = get_current_time();
		if (end_sleep >= start_sleep + sleep_time_ms)
			return (end_sleep);
		continue ;
	}
	return (-1);
}

void	print_message(long time_ms, int philo_num, t_state message)
{
	if (message == FORK)
		printf("%ld %d has taken a fork\n", time_ms, philo_num);
	else if (message == EAT)
		printf("%ld %d is eating\n", time_ms, philo_num);
	else if (message == SLEEP)
		printf("%ld %d is sleeping\n", time_ms, philo_num);
	else if (message == THINK)
		printf("%ld %d is thinking\n", time_ms, philo_num);
	else if (message == DIE)
		printf("\033[1;31m%ld %d is died\033[0m\n", time_ms, philo_num);
}

void	*testfunc(void *arg)
{
	(void) arg;
	print_message(12, 3, FORK);
	usleep(20000);
	print_message(12, 4, THINK);
	usleep(20000);
	print_message(12, 3, DIE);
	return (NULL);
}

void	*philos_routine(void *arg)
{
	t_coll	*coll;

	coll = (t_coll *)arg;
	write(1, "hello\n", 6);
	if (!coll)
	{
    	write(2, "Error: coll is NULL\n", 21);
    	return ((void *)1);
	}

	if (!(coll->th->fork))
	{
    	write(2, "Error: coll->th.fork is NULL\n", 30);
    	return ((void *)1);
	}
	if (pthread_mutex_lock(&(coll->th->fork[0])) != 0)
	{
		perror("Failed lock the fork mutex.\n");
		write(1, "hello3\n", 7);
		return ((void *)1);
	}
	write(1, "hello2\n", 7);
	printf("The philo[%d] are saying hello to you.\n", coll->ph->philo_id);
	pthread_mutex_unlock(&(coll->th->fork[0]));
	return ((void *)0);
}

void	free_memory(t_thread *th)
{
	free(th->philo);
	th->philo = NULL;
	free(th->fork);
	th->fork = NULL;
}

int	philo_threads(t_coll *coll)
{
	int	i;

	i = 0;
	coll->th->philo = malloc(coll->in->philo_num * sizeof(pthread_t));
	if (!coll->th->philo)
	{
		write_stderr("Malloc failed for philo threads allocation.\n");
		return (-1);
	}
	while (i < coll->in->philo_num)
	{
		coll->ph->philo_id = i + 1;
		if (pthread_create(&(coll->th->philo[i]), NULL,
				philos_routine, (void *)coll) != 0)
		{
			write_stderr("philo thread creation failed.\n");
			// return (free_memory(&(coll->th)), -2);
			return (-2);
		}
		// if (pthread_create(&(coll->th.philo[i]), NULL, testfunc, NULL) != 0)
		// {
		// 	write_stderr("philo thread creation failed.\n");
		// 	return (free_memory(&coll->th), -2);
		// }
		if (pthread_detach(coll->th->philo[i]) != 0)
		{
			write_stderr("philo thread detach failed.\n");
			// return (free_memory(&coll->th), -2);
			return(-2);
		}
		i++;
	}
	return (0);
}

int	one_philo(long start_t,long die_t)
{
	long	current_t;

	current_t = get_current_time();
	if (current_t < 0)
		return (-1);
	print_message(current_t - start_t, 1, FORK);
	my_usleep(die_t);
	usleep(1000);
	current_t = get_current_time();
	if (current_t < 0)
		return (-1);
	print_message(current_t - start_t, 1, DIE);
	return (0);
}

void	*print_monitor(void *arg)
{
	t_coll	*coll;
	int		i;
	long	sim_start_t;

	i = 0;
	coll = (t_coll *)arg;
	while (coll->th->start_t < 0)
	{
		usleep(10);
		continue ;
	}
	sim_start_t = get_current_time();
	if (sim_start_t < 0)
		return ((void * )(-1));
	while (i < coll->in->philo_num)
	{
		print_message(get_current_time() - coll->th->start_t, i + 1, THINK);
		i++;
	}
	if (coll->in->philo_num == 1)
		one_philo(coll->th->start_t, (long)coll->in->die_t);
	return(NULL);
}

int	print_thread(t_coll *coll)
{
	coll->th->start_t = -1;
	coll->ph->eat_start_t = -1;
	coll->th->fork = NULL;
	if (pthread_create(&(coll->th->monitor), NULL, print_monitor, (void *)coll) != 0)
	{
		write_stderr("monitor thread creation failed.\n");
		return (-1);
	}
	if (philo_threads(coll) < 0)
		return (-2);
	coll->th->start_t = get_current_time();
	if (coll->th->start_t < 0)
	{
		write_stderr("Failed to get the start_time");
		return (-3);
	}
	return (0);
}

int	create_mutexes(t_thread *th, int fork)
{
	int	i;

	i = 0;
	th->philo = NULL;
	th->fork = malloc(fork * sizeof(t_thread));
	if (!th->fork)
	{
		write_stderr("Failed allocate memory for fork.\n");
		return (-1);
	}
	while (i < fork)
	{
		if (pthread_mutex_init(&th->fork[i], NULL) != 0)
		{
			write_stderr("Failed to initialize the fork mutex.\n");
			while (i >= 0)
			{
				pthread_mutex_destroy(&th->fork[i]);
				i--;
			}
			return (-2);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_coll	coll;
	long	time_in_ms1;
	long	time_in_ms2;
	long	time_in_ms3;

	// pthread_create(&id, NULL, testfunc, NULL);
	write(1, "passed0\n", 8);
	if (!check_input(argc, argv, (coll.in)))
		return (1);
	write(1, "passed1\n", 8);
	if (create_mutexes(coll.th, coll.in->philo_num) < 0)
		return(1);
	// return(free_memory(&coll.th), 1);
	write(1, "passed2\n", 8);
	if (print_thread(&coll) < 0)
		return (1);
	// return (free_memory(&coll.th), 1);
	write(1, "passed3\n", 8);
	if (pthread_join(coll.th->monitor, NULL) != 0)
	{
		write_stderr("Failed to join the monitor thread.\n");
		return (1);
	}
	write(1, "passed4\n", 8);
	time_in_ms1 = get_current_time();
	printf("This is the store input: %d\n", coll.in->die_t);
	printf("The 0.current time is: %ld\n", time_in_ms1);
	my_usleep(20);
	time_in_ms2 = get_current_time();
	printf("The 1.current time is: %ld\n", time_in_ms2);
	printf("The elapsed time is: %ld\n", time_in_ms2 - time_in_ms1);
	my_usleep(60);
	time_in_ms3 = get_current_time();
	printf("The 2.current time is: %ld\n", time_in_ms3);
	printf("The elapsed time is: %ld\n", time_in_ms3 - time_in_ms1);
	// free_memory(&coll.th);
	return (0);
}
