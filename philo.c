/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:56:58 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/20 01:36:47 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>

#include "time.h"

void	philo_feedback(t_philo *philo, enum e_philo_action action)
{
	const char *feeback_msg[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};
	printf("%lld %d %s\n", get_time(), philo->id, feeback_msg[(int)action]);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_stick);
	pthread_mutex_lock(philo->right_stick);
	return (0);
}

void	*philo_thread(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo*)philo_v;
	printf("hey im a thread with id %d\n",philo->id);
	return (0);
}
