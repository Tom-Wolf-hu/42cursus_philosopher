/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:11:33 by tamas             #+#    #+#             */
/*   Updated: 2025/05/15 13:00:02 by tamas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int sleep_func(t_philo *ph, long sleep_t)
{
    ph->st = SLEEP;
    if (my_usleep(sleep_t) == -1)
    {
        write_stderr("\033[1;31mPhilosopher can't sleep enough time\033[0m\n");
        return (-1);
    }
    return (0);
}

int eat_func(t_philo *ph, long eat_t, int eat_num)
{
    ph->eat_start_t = get_current_time();
    if (ph->eat_start_t == -1)
        return (-1);
    ph->st = EAT;
    if (my_usleep(eat_t) == -1)
    {
        write_stderr("\033[1;31mPhilosopher can't eat enough time\033[0m\n");
        return (-1);
    }
    if (eat_num != -1)
        ph->meal_count++;
    return (0);
}

void    died_func(t_philo *ph, long die_time, long start_t)
{
    ph->smb_died = 1;
    ph->st = DIE;
    print_message(die_time - start_t, ph->philo_id, ph->st);
}
