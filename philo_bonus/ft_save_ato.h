/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_ato.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:06:14 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/21 00:05:19 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SAVE_ATO_H
# define FT_SAVE_ATO_H

int	save_atoi(const char *str, int *val);
int	save_atol(const char *str, long *val);
int	save_atoll(const char *str, long long *val);

#endif // FT_SAVE_ATO_H
