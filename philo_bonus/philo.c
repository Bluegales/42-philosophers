/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:56:58 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/21 04:44:10 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <semaphore.h>
#include <fcntl.h>	// For O_* constants
#include <sys/stat.h> // For mode constants

#include "time.h"


#include <stdio.h>

int	is_finished(t_philo *philo)
{
	int	error;

	error = sem_wait(philo->finished);
	if (error)
		return (1);
	sem_post(philo->finished);
	return (0);
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
					sem_post(philo->eaten_enough);
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
	if (is_finished(philo))
	{
		return(0);
	}
	if (philo->die_time < philo->eating_time || philo->die_time <= get_time())
	{
		wait_until(philo->die_time);
		philo_feedback(philo, e_philo_dead);
		sem_close(philo->finished);
		printf("killed it\n");
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
	philo->sticks = sem_open("sticks_sem", 0);
	philo->eaten_enough = sem_open("eaten_sem", 0);
	philo->finished = sem_open("finished_sem", 0);
	printf("%p\n%p\n%p\n", philo->sticks, philo->eaten_enough, philo->finished);
	philo->die_time = philo->param->start_time + philo->param->time_to_die;
	philo->eating_time = next_eat_time(philo);
	while (work(philo))
		;
	return (0);
}
