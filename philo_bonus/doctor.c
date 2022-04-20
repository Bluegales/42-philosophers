/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:59:20 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/20 07:35:29 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doctor.h"

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include "philo.h"
#include "time.h"

static void	kill_all(t_philo *philos)
{
	int	i;

	i = 0;
	//printf("killing all\n");
	while (i < philos->param->count)
	{
		{
			pthread_mutex_lock(&philos[i].time_dead_mutex);
			philos[i].time_dead = -1;
			pthread_mutex_unlock(&philos[i].time_dead_mutex);
		}
		i++;
	}
}

static int	philos_alive(t_philo *philos)
{
	int	i;
	int	alive;

	i = 0;
	alive = 0;
	while (i < philos->param->count)
	{
		{
			pthread_mutex_lock(&philos[i].time_dead_mutex);
			if (philos[i].time_dead != -1)
			{
				if (philos[i].time_dead < get_time())
				{
					//printf("%lld time dead %lld now\n", philos[i].time_dead, get_time());
					philos[i].time_dead = -1;
					philo_feedback_force(&philos[i], e_philo_dead);
				}
				else
					alive++;
			}
			pthread_mutex_unlock(&philos[i].time_dead_mutex);
		}
		i++;
	}
	return (alive);
}

static int	need_eat(t_philo *philos)
{
	int	i;
	int	need_eat;

	i = 0;
	need_eat = 0;
	while (i < philos->param->count)
	{
		{
			pthread_mutex_lock(&philos[i].number_eaten_mutex);
			if (philos[i].number_eaten < philos->param->number_to_eat)
				need_eat++;
			pthread_mutex_unlock(&philos[i].number_eaten_mutex);
			//printf("eaten %d\n", philos[i].number_eaten);
		}
		i++;
	}
	return (need_eat);
}

void	*doctor_thread(void *philos_v)
{
	t_philo	*philos;

	philos = (t_philo *)philos_v;

	while (1)
	{
		usleep(5 * 1000);
		//printf("checkup\n");
		if (philos_alive(philos) == 0)
		{
			return (0);
		}
		if (need_eat(philos) == 0)
		{
			kill_all(philos);
			return (0);
		}
	}
}
