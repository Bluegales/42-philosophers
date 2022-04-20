/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:59:20 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/21 00:50:19 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doctor.h"

#include <pthread.h> // mutex
#include <unistd.h> // usleep

#include "philo.h"
#include "time.h"

static void	kill_all_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->param->count)
	{
		{
			pthread_mutex_lock(&philos[i].finished_mutex);
			philos[i].finished = 1;
			pthread_mutex_unlock(&philos[i].finished_mutex);
		}
		i++;
	}
}

static int	philo_dead(t_philo *philos)
{
	int	i;
	int	dead;

	i = 0;
	dead = 0;
	while (i < philos->param->count)
	{
		{
			pthread_mutex_lock(&philos[i].finished_mutex);
			if (philos[i].finished)
				dead++;
			pthread_mutex_unlock(&philos[i].finished_mutex);
		}
		i++;
	}
	return (dead);
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
			if (philos[i].number_eaten < philos->param->number_to_eat
				&& !philos[i].finished)
				need_eat++;
			pthread_mutex_unlock(&philos[i].number_eaten_mutex);
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
		if (philo_dead(philos))
		{
			kill_all_philos(philos);
			return (0);
		}
		if (philos->param->number_to_eat != -1 && need_eat(philos) == 0)
		{
			kill_all_philos(philos);
			return (0);
		}
	}
}
