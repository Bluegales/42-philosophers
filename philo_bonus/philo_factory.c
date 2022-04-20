/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_factory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:26:29 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/20 09:04:57 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_factory.h"

#include <pthread.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#include "philo.h"

void	philo_factory_cleanup(t_philo_factory *factory)
{
	free(factory->philos);
	free(factory->threads);
	free(factory->returns);
}

static void	set_start_data(t_philo *philo, const t_philo_param *param, int id)
{
	sem_open("asd", O_CREAT, 0, 0);

	philo->id = id;
	philo->number_eaten = 0;
	philo->param = param;
	philo->time_dead = 0;
	pthread_mutex_init(&philo->time_dead_mutex, NULL);
	pthread_mutex_init(&philo->left_stick, NULL);
	pthread_mutex_init(&philo->number_eaten_mutex, NULL);
	if (id + 1 != param->count)
		philo->right_stick = &(philo + 1)->left_stick;
	else
		philo->right_stick = &(philo - id)->left_stick;
}

int	philo_factory_init(t_philo_factory *factory, const t_philo_param *param)
{
	int	i;

	factory->count = param->count;
	factory->philos = malloc(sizeof(t_philo) * param->count);
	factory->threads = malloc(sizeof(pthread_t) * param->count);
	factory->returns = malloc(sizeof(int) * param->count);
	if (!factory->philos || !factory->threads || !factory->returns)
	{
		philo_factory_cleanup(factory);
		return (1);
	}
	i = 0;
	while (i < param->count)
	{
		set_start_data(&factory->philos[i], param, i);
		i++;
	}
	return (0);
}

int	philo_factory_start(t_philo_factory *factory)
{
	int				i;
	int				error;

	i = 0;
	error = 0;
	while (i < factory->count)
	{
		error += pthread_create(&factory->threads[i], NULL, philo_thread,
			(void *)&factory->philos[i]);
		i++;
	}
	return (0);
}

int	philo_factory_join(t_philo_factory *factory)
{
	int				i;
	int				error;

	i = 0;
	error = 0;
	while (i < factory->count)
	{
		error += pthread_join(factory->threads[i], NULL);
		i++;
	}
	return (0);
}
