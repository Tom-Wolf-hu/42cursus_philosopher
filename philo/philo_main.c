/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:02:05 by tfarkas           #+#    #+#             */
/*   Updated: 2025/05/17 10:33:10 by tamas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	*philos_routine(void *arg)
{
	t_coll	*coll;

	coll = (t_coll *)arg;
	// if (!coll->fork || pthread_mutex_lock(&(coll->fork[0])) != 0)
	// {
	// 	perror("\033[1;35mFailed lock the fork mutex\033[0m");
	// 	return ((void *)1);
	// }
	// pthread_mutex_lock(&coll->control);
	printf("The philo[%d] are saying hello to you.\n", coll->ph.philo_id);
	// pthread_mutex_unlock(&(coll->fork[0]));
	// pthread_mutex_unlock(&coll->control);
	return ((void *)0);
}

int	philo_threads(t_coll *coll)
{
	int	i;

	i = 0;
	coll->th.philo = malloc(coll->in.philo_num * sizeof(pthread_t));
	if (!coll->th.philo)
	{
		write_stderr("Malloc failed for philo threads allocation.\n");
		return (-1);
	}
	while (i < coll->in.philo_num)
	{
		pthread_mutex_lock(&coll->control);
		coll->ph.philo_id = i + 1;
		fprintf(stderr, "The philo_num: %d in philo_threads function.\n", coll->ph.philo_id);
		pthread_mutex_unlock(&coll->control);
		if (pthread_create(&(coll->th.philo[i]), NULL,
				philos_routine, (void *)coll) != 0)
		{
			write_stderr("philo thread creation failed.\n");
			return (-2);
		}
		// if (pthread_create(&(coll->th.philo[i]), NULL, testfunc, NULL) != 0)
		// {
		// 	write_stderr("philo thread creation failed.\n");
		// 	return (free_memory(&coll->th), -2);
		// }
		if (pthread_detach(coll->th.philo[i]) != 0)
		{
			write_stderr("philo thread detach failed.\n");
			return(-2);
		}
		i++;
	}
	return (0);
}

void	*print_monitor(void *arg)
{
	t_coll	*coll;
	int		i;

	i = 0;
	coll = (t_coll *)arg;
	while (coll->th.start_t < 0)
	{
		usleep(10);
		continue ;
	}
	while (i < coll->in.philo_num)
	{
		print_message(get_current_time() - coll->th.start_t, i + 1, THINK);
		i++;
	}
	if (coll->in.philo_num == 1)
		one_philo(coll->th.start_t, (long)coll->in.die_t);
	// else
	// 	more_philo(coll);
	return((void *)0);
}

int	print_thread(t_coll *coll)
{
	coll->th.start_t = -1;
	coll->ph.eat_start_t = -1;
	if (pthread_create(&(coll->th.monitor), NULL, print_monitor, (void *)coll) != 0)
	{
		write_stderr("monitor thread creation failed.\n");
		return (-1);
	}
	if (philo_threads(coll) < 0)
		return (-2);
	coll->th.start_t = get_current_time();
	if (coll->th.start_t < 0)
	{
		write_stderr("Failed to get the start_time");
		return (-3);
	}
	return (0);
}

int	create_fork_mutexes(t_coll *coll)
{
    int	i;

    i = 0;
    coll->fork = malloc(coll->in.philo_num * sizeof(pthread_mutex_t));
    if (!coll->fork)
    {
        write_stderr("Failed to allocate memory for fork mutexes.\n");
        return (-1);
    }
    while (i < coll->in.philo_num)
    {
        if (pthread_mutex_init(&coll->fork[i], NULL) != 0)
        {
            write_stderr("Failed to initialize a fork mutex.\n");
            while (--i >= 0)
                pthread_mutex_destroy(&coll->fork[i]);
            free(coll->fork);
            coll->fork = NULL;
            return (-2);
        }
        i++;
    }
    return (0);
}

int	create_control_mutex(t_coll *coll)
{
	if (pthread_mutex_init(&coll->control, NULL) != 0)
	{
		write_stderr("The control mutex initialization failed.\n");
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_coll	coll;

	// pthread_create(&id, NULL, testfunc, NULL);
	write(1, "passed0\n", 8);
	if (!check_input(argc, argv, &coll.in))
		return (1);
	write(1, "passed1\n", 8);
	if (!coll_init(&coll))
		return (1);
	if (create_control_mutex(&coll) < 0)
		return (1);
	if (create_fork_mutexes(&coll) < 0)
		return (free_memory(&coll), 1);
	write(1, "passed2\n", 8);
	if (!coll.fork)
		printf("\033[1,33mthe coll fork NULL before print_thread\n\033m");
	if (print_thread(&coll) < 0)
		return (free_memory(&coll), 1);
	write(1, "passed3\n", 8);
	if (pthread_join(coll.th.monitor, NULL) != 0)
	{
		write_stderr("Failed to join the monitor thread.\n");
		return (1);
	}
	write(1, "passed4\n", 8);
	main_thread_print(&coll);
	free_memory(&coll);
	return (0);
}
