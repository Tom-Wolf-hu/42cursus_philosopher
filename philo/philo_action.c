/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamas <tamas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:11:33 by tamas             #+#    #+#             */
/*   Updated: 2025/05/17 21:44:44 by tamas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int sleep_func(t_philo *ph)
{
    ph->st = SLEEP;
    ph->state_changed = 1;
    if (my_usleep(ph->sleep_time) == -1)
    {
        write_stderr("\033[1;31mPhilosopher can't sleep enough time\033[0m\n");
        return (-1);
    }
    return (0);
}

int eat_func(t_philo *ph)
{
    ph->eat_start_t = get_current_time();
    if (ph->eat_start_t == -1)
        return (-1);
    ph->st = EAT;
    ph->state_changed = 1;
    if (my_usleep(ph->eat_time) == -1)
    {
        write_stderr("\033[1;31mPhilosopher can't eat enough time\033[0m\n");
        return (-1);
    }
    if (ph->meal_count != -1)
        ph->meal_count++;
    return (0);
}
