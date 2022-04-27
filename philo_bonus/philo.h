/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:56:54 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/27 03:33:08 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <semaphore.h>

# include "time.h" // t_ms

typedef struct s_philo_param
{
	int		count;
	int		number_to_eat;
	t_ms	start_time;
	t_ms	time_to_die;
	t_ms	time_to_eat;
	t_ms	time_to_sleep;
}	t_philo_param;

typedef struct s_philo
{
	const t_philo_param		*param;
	int						id;
	t_ms					die_time;
	t_ms					eating_time;
	sem_t					*sticks;
	sem_t					*eaten_enough;
	sem_t					*print;
	int						number_eaten;
}	t_philo;

enum	e_philo_action {
	e_philo_stick = 0,
	e_philo_eat = 1,
	e_philo_sleep = 2,
	e_philo_think = 3,
	e_philo_dead = 4
};

void	philo_feedback(t_philo *philo, enum e_philo_action action);
t_ms	next_eat_time(const t_philo *philo);
void	*philo_thread(void *philo);
int		is_finished(void);

#endif // PHILO_H
