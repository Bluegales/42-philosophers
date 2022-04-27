/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:56:58 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/27 03:46:42 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <semaphore.h>
#include <fcntl.h>	// For O_* constants
#include <sys/stat.h> // For mode constants

#include "time.h"

static void	finish(void)
{
	sem_t	*finished;

	finished = sem_open("/finished", O_CREAT, 0644, 9999);
}

static void	eat(t_philo *philo)
{
	t_ms	time;

	time = get_time();
	if (philo->die_time > time)
	{
		philo->die_time = time + philo->param->time_to_die;
		philo_feedback(philo, e_philo_eat);
		{
			if (philo->param->number_to_eat != -1)
			{
				philo->number_eaten++;
				if (philo->number_eaten == philo->param->number_to_eat)
					finish();
			}
		}
		wait_until(time + philo->param->time_to_eat);
	}
}

static void	take_sticks(t_philo *philo)
{
	{
		sem_wait(philo->sticks);
		philo_feedback(philo, e_philo_stick);
		{
			sem_wait(philo->sticks);
			philo_feedback(philo, e_philo_stick);
			eat(philo);
			sem_post(philo->sticks);
		}
		sem_post(philo->sticks);
	}
	philo_feedback(philo, e_philo_sleep);
	if (philo->die_time < get_time() + philo->param->time_to_sleep)
	{
		wait_until(philo->die_time);
		return ;
	}
	wait_until(get_time() + philo->param->time_to_sleep);
	philo_feedback(philo, e_philo_think);
}

static int	work(t_philo *philo)
{
	if (is_finished())
	{
		return (0);
	}
	if (philo->die_time < philo->eating_time || philo->die_time <= get_time())
	{
		wait_until(philo->die_time);
		philo_feedback(philo, e_philo_dead);
		return (0);
	}
	wait_until(philo->eating_time);
	take_sticks(philo);
	philo->eating_time = next_eat_time(philo);
	return (1);
}

void	*philo_thread(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	philo->die_time = philo->param->start_time + philo->param->time_to_die;
	philo->eating_time = next_eat_time(philo);
	while (work(philo))
		;
	finish();
	return (0);
}
