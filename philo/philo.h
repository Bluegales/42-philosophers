/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:56:54 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/21 00:54:18 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <pthread.h> // cant typedef pthread because norm
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
	pthread_mutex_t			left_stick;
	pthread_mutex_t			*right_stick;
	pthread_mutex_t			*first_stick;
	pthread_mutex_t			*second_stick;
	int						number_eaten;
	pthread_mutex_t			number_eaten_mutex;
	int						finished;
	pthread_mutex_t			finished_mutex;
}	t_philo;

enum	e_philo_action {
	e_philo_stick = 0,
	e_philo_eat = 1,
	e_philo_sleep = 2,
	e_philo_think = 3,
	e_philo_dead = 4
};

void	philo_feedback(t_philo *philo, enum e_philo_action action);
int		is_finished(t_philo *philo);
t_ms	next_eat_time(const t_philo *philo);
void	*philo_thread(void *philo);

#endif // PHILO_H
