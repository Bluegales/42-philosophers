/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:26:04 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/20 07:16:19 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_factory.h"
#include "philo.h"
#include "time.h"
#include "doctor.h"

#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_philo_param	params;
	t_philo_factory	factory;
	pthread_t		doctor;

	params.count = atoi(argv[1]);
	params.number_to_eat = 99999999;
	if (argc == 6)
		params.number_to_eat = atoi(argv[5]);
	params.time_to_die = atoi(argv[2]);
	params.time_to_eat = atoi(argv[3]);
	params.time_to_sleep = atoi(argv[4]);
	printf("count: %d, die: %lld, eat %lld, sleep %lld, number_eat %d\n", params.count, params.time_to_die, params.time_to_eat, params.time_to_sleep, params.number_to_eat);
	params.start_time = get_time();
	philo_factory_init(&factory, &params);
	philo_factory_start(&factory);
	pthread_create(&doctor, NULL, doctor_thread, (void *)factory.philos);
	philo_factory_join(&factory);
	pthread_join(doctor, NULL);
	return 0;
}
