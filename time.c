/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:06:35 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/20 00:12:12 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"

#include <sys/time.h>
#include <stddef.h>

ms	get_time()
{
	struct timeval	time;
	ms				ms_time;

	if (gettimeofday(&time, NULL))
		return (-1);
	ms_time = (long long)time.tv_sec * 1000;
	ms_time += time.tv_usec % 1000;
	return (ms_time);
}
