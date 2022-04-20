/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_factory.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:26:37 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/21 00:53:05 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_FACTORY_H
# define PHILO_FACTORY_H

# include <pthread.h> // cant typedef pthread because norm

# include "philo.h"

typedef struct s_philo_factory	t_philo_factory;

typedef struct s_philo_factory
{
	t_philo			*philos;
	pthread_t		*threads;
	int				*returns;
	int				count;
}	t_philo_factory;

void	philo_factory_cleanup(t_philo_factory *factory);
int		philo_factory_init(t_philo_factory *factory,
			const t_philo_param *param);
int		philo_factory_start(t_philo_factory *factory);
int		philo_factory_join(t_philo_factory *factory);

#endif // PHILO_FACTORY_H
