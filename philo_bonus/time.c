/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:06:35 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/21 00:54:57 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"

#include <sys/time.h> // gettimeofday
#include <unistd.h> // usleep
#include <stddef.h> // NULL

t_ms	get_time(void)
{
	struct timeval		time;
	t_ms				ms_time;

	if (gettimeofday(&time, NULL))
		return (-1);
	ms_time = (long long)time.tv_sec * 1000;
	ms_time += (long long)(time.tv_usec / 1000);
	return (ms_time);
}

void	wait_until(t_ms wakeup_time)
{
	const int	margin = 2;
	t_ms		time;

	time = get_time();
	while (wakeup_time - time > margin)
	{
		usleep(1000 * (wakeup_time - time - margin));
		time = get_time();
	}
	while (wakeup_time > time)
		time = get_time();
}
