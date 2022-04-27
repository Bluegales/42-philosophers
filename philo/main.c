/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:26:04 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/27 03:11:44 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //printf

#include "ft_save_ato.h"
#include "philo_factory.h"
#include "philo.h"
#include "time.h"
#include "doctor.h"

void	print_usage(void)
{
	printf("Usage: philo number_of_philosophers time_to_die time_to_eat "
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
}

int	parse(int argc, char **argv, t_philo_param *param)
{
	if (argc != 5 && argc != 6)
		return (1);
	param->number_to_eat = -1;
	if (argc == 6)
	{
		if (save_atoi(argv[5], &param->number_to_eat) == -1)
			return (1);
	}
	if (save_atoi(argv[1], &param->count) == -1)
		return (1);
	if (save_atoll(argv[2], &param->time_to_die) == -1)
		return (1);
	if (save_atoll(argv[3], &param->time_to_eat) == -1)
		return (1);
	if (save_atoll(argv[4], &param->time_to_sleep) == -1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_param	params;
	t_philo_factory	factory;
	pthread_t		doctor;

	if (parse(argc, argv, &params))
	{
		print_usage();
		return (0);
	}
	params.start_time = get_time();
	if (params.count == 1)
	{
		wait_until(params.start_time + params.time_to_die);
		printf("%lld %d %s\n", get_time() - params.start_time,
			0, "died");
		return (0);
	}
	philo_factory_init(&factory, &params);
	philo_factory_start(&factory);
	pthread_create(&doctor, NULL, doctor_thread, (void *)factory.philos);
	philo_factory_join(&factory);
	pthread_join(doctor, NULL);
	philo_factory_cleanup(&factory);
	return (0);
}
