/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_factory.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:26:37 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/20 03:06:35 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B68AB8E8_FBB6_45FB_B17E_3446C3DA7B48
#define B68AB8E8_FBB6_45FB_B17E_3446C3DA7B48

#include "philo.h"

#include <pthread.h>

typedef struct s_philo_factory
{
	t_philo			*philos;
	pthread_t		*threads;
	int				*returns;
	int				count;
}	t_philo_factory;

void	philo_factory_cleanup(t_philo_factory *factory);
int	philo_factory_init(t_philo_factory *factory, const t_philo_param *param);
int	philo_factory_start(t_philo_factory *factory);
int	philo_factory_join(t_philo_factory *factory);

#endif /* B68AB8E8_FBB6_45FB_B17E_3446C3DA7B48 */
