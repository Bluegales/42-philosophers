/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:26:04 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/20 01:19:14 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_factory.h"
#include "philo.h"

#include <stdio.h>

int	main()
{
	t_philo_defaults	defaults;
	t_philo_factory		factory;

	defaults.philo_count = 2;
	defaults.time_to_die = 20;
	defaults.time_to_eat = 20;
	defaults.time_to_sleep = 20;
	philo_factory_init(&factory, 2);
	philo_factory_start(&factory);
	philo_factory_join(&factory);
	return 0;
}
