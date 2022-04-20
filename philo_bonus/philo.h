/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:56:54 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/20 08:56:51 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "pthread.h"

#include <semaphore.h>
# include "time.h"

typedef struct s_philo_param
{
	int	count;
	int	number_to_eat;
	ms	start_time;
	ms	time_to_die;
	ms	time_to_eat;
	ms	time_to_sleep;
}	t_philo_param;

typedef struct s_philo
{
	const t_philo_param		*param;
	int		id;
	int		number_eaten;
	ms		time_dead;
	sem_t	sticks;
}	t_philo;

enum	e_philo_action {
	e_philo_stick = 0,
	e_philo_eat = 1,
	e_philo_sleep = 2,
	e_philo_think = 3,
	e_philo_dead = 4
};

void	philo_feedback(t_philo *philo, enum e_philo_action action);
void	philo_feedback_force(t_philo *philo, enum e_philo_action action);
void	*philo_thread(void *philo);

#endif // PHILOSOPHER_H
