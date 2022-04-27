/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:47:53 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/27 03:20:45 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h> // printf

void	philo_feedback(t_philo *philo, enum e_philo_action action)
{
	int			cancel;
	const char	*msg[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

	cancel = 0;
	{
		pthread_mutex_lock(&philo->finished_mutex);
		if (philo->finished)
			cancel = 1;
		pthread_mutex_unlock(&philo->finished_mutex);
	}
	if (cancel)
		return ;
	if (action == e_philo_dead || philo->die_time > get_time())
	{
		printf("%lld %d %s\n", get_time() - philo->param->start_time,
			philo->id + 1, msg[(int)action]);
	}
}

int	is_finished(t_philo *philo)
{
	int	finished;

	finished = 0;
	{
		pthread_mutex_lock(&philo->finished_mutex);
		if (philo->finished)
			finished = 1;
		pthread_mutex_unlock(&philo->finished_mutex);
	}
	return (finished);
}

t_ms	next_eat_time(const t_philo *philo)
{
	int		eat_rotation;
	t_ms	rotation_time;
	int		eat_id;

	rotation_time = philo->param->time_to_eat + 1;
	if (rotation_time < philo->param->time_to_sleep + 1)
		rotation_time = philo->param->time_to_sleep + 1;
	eat_rotation = get_time() - philo->param->start_time;
	eat_rotation /= rotation_time;
	while (1)
	{
		eat_id = ((philo->id + eat_rotation) % philo->param->count);
		if (eat_id % 2 == 0 && eat_id != philo->param->count - 1)
			return (philo->param->start_time + rotation_time * eat_rotation);
		eat_rotation++;
	}
}
