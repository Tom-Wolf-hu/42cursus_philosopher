/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarkas <tfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:02:05 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/09 14:42:23 by tfarkas          ###   ########.fr       */
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
		printf("%ld %d is died\n", time_ms, philo_num);
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

void	free_memory(t_thread *th)
{
	free(th->philo);
	th->philo = 0;
}

int	philo_threads(t_input in_args, t_thread *th)
{
	int	i;

	i = 0;
	th->philo = malloc(in_args.philo_num * sizeof(pthread_t));
	if (!th->philo)
	{
		write_stderr("Malloc failed for philo threads allocation.\n");
		return (-1);
	}
	while (i < in_args.philo_num)
	{
		if (pthread_create(&th->philo[i], NULL, testfunc, NULL) != 0)
		{
			write_stderr("philo thread creation failed.\n");
			return (free_memory(th), -2);
		}
		if (pthread_detach(th->philo[i]) != 0)
		{
			write_stderr("philo thread detach failed.\n");
			return (free_memory(th), -2);
		}
		i++;
	}
	return (0);
}

void	*print_monitor(void *arg)
{
	t_coll	*coll;
	int	i;

	i = 0;
	coll = (t_coll *)arg;
	while (coll->th.start_t < 0)
	{
		usleep(10);
		continue ;
	}
	printf("The simulation start time: %ld\n", coll->th.start_t);
	while (i < coll->in.philo_num)
	{
		print_message(get_current_time() - coll->th.start_t, i + 1, THINK);
		i++;
	}
	return(NULL);
}

int	print_thread(t_coll *coll)
{
	coll->th.start_t = -1;
	coll->ph.eat_start_t = -1;
	if (pthread_create(&coll->th.monitor, NULL, print_monitor, (void *)coll) != 0)
	{
		write_stderr("monitor thread creation failed.\n");
		return (-1);
	}
	if (philo_threads(coll->in, &(coll->th)) < 0)
		return (-2);
	coll->th.start_t = get_current_time();
	if (coll->th.start_t < 0)
	{
		write_stderr("Failed to get the start_time");
		return (-3);
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
	if (!check_input(argc, argv, &coll.in))
		return (1);
	if (print_thread(&coll) < 0)
		return (1);
	pthread_join(coll.th.monitor, NULL);
	time_in_ms1 = get_current_time();
	printf("This is the store input: %d\n", coll.in.die_t);
	printf("The 0.current time is: %ld\n", time_in_ms1);
	my_usleep(20);
	time_in_ms2 = get_current_time();
	printf("The 1.current time is: %ld\n", time_in_ms2);
	printf("The elapsed time is: %ld\n", time_in_ms2 - time_in_ms1);
	my_usleep(60);
	time_in_ms3 = get_current_time();
	printf("The 2.current time is: %ld\n", time_in_ms3);
	printf("The elapsed time is: %ld\n", time_in_ms3 - time_in_ms1);
	free_memory(&coll.th);
	return (0);
}
