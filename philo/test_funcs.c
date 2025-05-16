/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:55:12 by tamas             #+#    #+#             */
/*   Updated: 2025/05/16 13:00:49 by tamas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	main_thread_print(t_coll *coll)
{
	long	time_in_ms1;
	long	time_in_ms2;
	long	time_in_ms3;
	
	time_in_ms1 = get_current_time();
	printf("This is the store input: %d\n", coll->in.die_t);
	printf("The 0.current time is: %ld\n", time_in_ms1);
	my_usleep(20);
	time_in_ms2 = get_current_time();
	printf("The 1.current time is: %ld\n", time_in_ms2);
	printf("The elapsed time is: %ld\n", time_in_ms2 - time_in_ms1);
	my_usleep(60);
	time_in_ms3 = get_current_time();
	printf("The 2.current time is: %ld\n", time_in_ms3);
	printf("The elapsed time is: %ld\n", time_in_ms3 - time_in_ms1);
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
