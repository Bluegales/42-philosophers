/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_factory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:26:29 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/21 00:25:08 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_factory.h"

#include <pthread.h>
#include <stdlib.h>

#include "philo.h"

void	philo_factory_cleanup(t_philo_factory *factory)
{
	int	i;

	i = 0;
	while (i < factory->count)
	{
		pthread_mutex_destroy(&factory->philos[i].finished_mutex);
		pthread_mutex_destroy(&factory->philos[i].number_eaten_mutex);
		pthread_mutex_destroy(&factory->philos[i].left_stick);
		i++;
	}
	free(factory->philos);
	free(factory->threads);
	free(factory->returns);
}

static void	set_start_data(t_philo *philo, const t_philo_param *param, int id)
{
	philo->id = id;
	philo->finished = 0;
	philo->number_eaten = 0;
	philo->param = param;
	pthread_mutex_init(&philo->finished_mutex, NULL);
	pthread_mutex_init(&philo->number_eaten_mutex, NULL);
	pthread_mutex_init(&philo->left_stick, NULL);
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
