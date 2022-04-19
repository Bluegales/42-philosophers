/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:59:20 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/20 00:54:24 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doctor.h"

#include <pthread.h>
#include <unistd.h>

#include "philo.h"
#include "time.h"

int	doctor_check(t_philo *philos)
{
	while (philos->id != -1)
	{
		pthread_mutex_lock(&philos->time_dead_mutex);
		if (philos->time_dead < get_time())
		philo_feedback(philos, e_philo_dead);
		pthread_mutex_unlock(&philos->time_dead_mutex);
		philos++;
	}
	return (0);
}

void	doctor_thread(t_philo *philos)
{
	int	run;

	run = 1;
	while (run)
	{
		usleep(5 * 1000);
		doctor_check(philos);
	}
}
