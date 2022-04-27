/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_factory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:26:29 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/27 03:44:34 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_factory.h"

#include <unistd.h> //fork
#include <semaphore.h>
#include <fcntl.h>	// For O_* constants
#include <sys/stat.h> // For mode constants

#include <sys/types.h>
#include <sys/wait.h>

#include "philo.h"

static void	set_start_data(t_philo *philo, const t_philo_param *param, int id)
{
	philo->id = id;
	philo->number_eaten = 0;
	philo->param = param;
}

static void	init_sem(t_philo_param *param, t_philo *philo)
{
	sem_unlink("/sticks");
	sem_unlink("/eaten");
	sem_unlink("/finished");
	sem_unlink("/print");
	philo->sticks = sem_open("/sticks", O_CREAT, 0644, param->count);
	philo->print = sem_open("/print", O_CREAT, 0644, 1);
	philo->eaten_enough = sem_open("/eaten", O_CREAT, 0644, 0);
	sem_unlink("/sticks");
	sem_unlink("/eaten");
	sem_unlink("/print");
}

static void	wait_for_children(t_philo_param *param)
{
	int	i;

	i = 0;
	while (i < param->count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

int	philo_factory_start(t_philo_param *param)
{
	t_philo		philo;
	pid_t		id;
	int			i;

	i = 0;
	init_sem(param, &philo);
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
	if (id != 0)
	{
		wait_for_children(param);
	}
	sem_unlink("/finished");
	return (0);
}
