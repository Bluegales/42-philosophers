/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:56:58 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/20 07:54:23 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>
#include <unistd.h>

#include "time.h"

static const char *msg[] = {
	"has taken a fork",
	"is eating",
	"is sleeping",
	"is thinking",
	"died"
};

void	philo_feedback_force(t_philo *philo, enum e_philo_action action)
{
	printf("%lld %d %s\n", get_time() - philo->param->start_time, philo->id, msg[(int)action]);
}

void	philo_feedback(t_philo *philo, enum e_philo_action action)
{
	pthread_mutex_lock(&philo->time_dead_mutex);
	if (philo->time_dead != -1)
		philo_feedback_force(philo, action);
	pthread_mutex_unlock(&philo->time_dead_mutex);
}

static int	philo_alive(t_philo *philo)
{
	int	alive;

	alive = 1;
	{
		pthread_mutex_lock(&philo->time_dead_mutex);
		if (philo->time_dead == -1)
			alive = 1;
		pthread_mutex_unlock(&philo->time_dead_mutex);
	}
	return (alive);
}

static void	eat_with_sticks(t_philo *philo)
{
	int alive;

	alive = 0;
	{
		pthread_mutex_lock(&philo->time_dead_mutex);
		if (philo->time_dead > get_time())
		{
			//printf("not dead\n");
			philo->time_dead = get_time() + philo->param->time_to_die;
			philo_feedback_force(philo, e_philo_eat);
			alive = 1;
		}
		pthread_mutex_unlock(&philo->time_dead_mutex);
	}
	if (!alive)
		return;
	pthread_mutex_lock(&philo->number_eaten_mutex);
	(philo->number_eaten)++;
	pthread_mutex_unlock(&philo->number_eaten_mutex);
	usleep(1000 * philo->param->time_to_eat);
	philo_feedback(philo, e_philo_sleep);
}

static void	eat(t_philo *philo)
{
	if (!philo_alive(philo))
		return ;
	{
		pthread_mutex_lock(&philo->left_stick);
		philo_feedback(philo, e_philo_stick);
		{
			pthread_mutex_lock(philo->right_stick);
			philo_feedback(philo, e_philo_stick);
			eat_with_sticks(philo);
			pthread_mutex_unlock(philo->right_stick);
		}
	pthread_mutex_unlock(&philo->left_stick);
	}
	usleep(1000 * philo->param->time_to_sleep);
	philo_feedback(philo, e_philo_think);
}

static ms	next_eat_time(const t_philo *philo)
{
	int	eat_rotation;
	ms	rotation_time;
	int	eat_id;

	rotation_time = philo->param->time_to_eat;
	if (rotation_time < philo->param->time_to_sleep)
		rotation_time = philo->param->time_to_sleep;
	eat_rotation = get_time() - philo->param->start_time;
	eat_rotation /= rotation_time;
	while (1)
	{
		eat_id = ((philo->id + eat_rotation) % philo->param->count);
		//printf("id: %d eat: %d at rotation: %d\n", philo->id, eat_id, eat_rotation);
		if (eat_id % 2 == 0 && eat_id != philo->param->count - 1)
			return (philo->param->start_time + rotation_time * eat_rotation);
		eat_rotation++;
	}
}

void	*philo_thread(void *philo_v)
{
	t_philo	*philo;
	int		alive;

	philo = (t_philo*)philo_v;
	alive = 1;
	{
		pthread_mutex_lock(&philo->time_dead_mutex);
			philo->time_dead = get_time() + philo->param->time_to_die;
		pthread_mutex_unlock(&philo->time_dead_mutex);
	}
	while (alive)
	{
		if (next_eat_time(philo) - get_time() > 0)
			usleep(1000 * (next_eat_time(philo) - get_time() - 1));
		eat(philo);
		{
			pthread_mutex_lock(&philo->time_dead_mutex);
			if (philo->time_dead == -1)
				alive = 0;
			pthread_mutex_unlock(&philo->time_dead_mutex);
		}
	}
	return (0);
}
