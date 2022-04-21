/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:06:56 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/21 03:00:25 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

typedef long long	t_ms;

t_ms	get_time(void);
void	wait_until(t_ms wakeup_time);

#endif // TIME_H
