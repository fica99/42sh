/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 19:39:28 by aashara-          #+#    #+#             */
/*   Updated: 2018/12/25 14:35:52 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	res;
	size_t				s_len;

	sign = 1;
	res = 0;
	while (*str == '\t' || *str == '\v' || *str == '\f' || *str == '\r'
			|| *str == '\n' || *str == ' ')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	s_len = 0;
	while (*str >= 48 && *str <= 57)
	{
		res *= 10;
		res += *str - '0';
		str++;
		if (res > LLONG_MAX || (res < ULLONG_MAX && ++s_len >= 20))
			return (sign == 1 ? -1 : 0);
	}
	return (sign * (int)res);
}
