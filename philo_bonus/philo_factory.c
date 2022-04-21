/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_factory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:26:29 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/21 04:28:41 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_factory.h"

#include <unistd.h> //fork
#include <semaphore.h>
#include <fcntl.h>	// For O_* constants
#include <sys/stat.h> // For mode constants

#include "philo.h"

static void	set_start_data(t_philo *philo, const t_philo_param *param, int id)
{
	philo->id = id;
	philo->number_eaten = 0;
	philo->param = param;
}

#include <stdio.h>

int	philo_factory_start(t_philo_param *param)
{
	t_philo		philo;
	pid_t		id;
	int			i;

	i = 0;
	philo.sticks = sem_open("sticks_sem", O_CREAT, 0644, param->count);
	philo.eaten_enough = sem_open("eaten_sem", O_CREAT, 0644, param->count);
	philo.finished = sem_open("finished_sem", O_CREAT, 0644, param->count);
	printf("%p\n%p\n%p\n", philo.sticks, philo.eaten_enough, philo.finished);
	while (i < param->count)
	{
		id = fork();
		if (id == 0)
		{
			set_start_data(&philo, param, i);
			philo_thread(&philo);
			return (0);
		}
		if (id != -1)
			i++;
	}
	return (0);
}
