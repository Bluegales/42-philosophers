/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:47:53 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/21 04:41:22 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <semaphore.h>

#include <stdio.h> // printf

void	philo_feedback(t_philo *philo, enum e_philo_action action)
{
	int			error;
	const char	*msg[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

	error = sem_wait(philo->finished);
	if (error)
		return;
	printf("got error: %d\n", error);
	sem_post(philo->finished);
	if (action == e_philo_dead || philo->die_time > get_time())
	{
		printf("%lld %d %s\n", get_time() - philo->param->start_time,
			philo->id, msg[(int)action]);
	}
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
