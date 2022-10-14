/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_atoll.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:45:30 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/21 00:46:29 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_save_ato.h"

#include <limits.h>
#include <stdio.h>

static int	convert_sign(int sign, long long *val, char c)
{
	if (c != 0)
	{
		return (2);
	}
	if (*val == LLONG_MIN && !sign)
	{
		*val = LLONG_MAX;
		return (-1);
	}
	if (!sign)
		*val *= -1;
	return (0);
}

static int	test_overflow(int sign, long long *val)
{
	if (*val > 0)
	{
		*val = LLONG_MAX;
		if (sign)
			*val = LLONG_MIN;
		return (2);
	}
	return (0);
}

// returns 0 on succress, -1 on no number, 1 on char, 2 on overflow
int	save_atoll(const char *str, long long *val)
{
	int	sign;

	sign = 0;
	*val = 0;
	if (*str == '-')
		sign = 1;
	if (*str == '-' || *str == '+')
		str++;
	if (*str < '0' || *str > '9')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		*val *= 10;
		if (test_overflow(sign, val))
			return (2);
		*val -= *str - '0';
		str++;
	}
	if (convert_sign(sign, val, *str))
		return (2);
	if (*str == '\0')
		return (0);
	return (1);
}
