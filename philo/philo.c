/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:56:58 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/21 00:53:53 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "time.h"

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
				pthread_mutex_lock(&philo->number_eaten_mutex);
				(philo->number_eaten)++;
				pthread_mutex_unlock(&philo->number_eaten_mutex);
			}
		}
		wait_until(time + philo->param->time_to_eat);
	}
}

static void	take_sticks(t_philo *philo)
{
	{
		pthread_mutex_lock(&philo->left_stick);
		philo_feedback(philo, e_philo_stick);
		{
			pthread_mutex_lock(philo->right_stick);
			philo_feedback(philo, e_philo_stick);
			eat(philo);
			pthread_mutex_unlock(philo->right_stick);
		}
		pthread_mutex_unlock(&philo->left_stick);
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
		return (0);
	if (philo->die_time < philo->eating_time || philo->die_time <= get_time())
	{
		wait_until(philo->die_time);
		philo_feedback(philo, e_philo_dead);
		{
			pthread_mutex_lock(&philo->finished_mutex);
			philo->finished = 1;
			pthread_mutex_unlock(&philo->finished_mutex);
		}
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
	return (0);
}
