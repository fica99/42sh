/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 22:09:11 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/11 23:33:10 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

static int	calc_digit(long long num)
{
	int	digit;

	digit = 1;
	if (!num)
		return (digit);
	while ((num /= 10) > 0)
		digit++;
	return (digit);
}

static void	calc_ltoa_rec(long num, char *str, int index)
{
	if (num >= 10)
		calc_ltoa_rec(num / 10, str, index - 1);
	str[index] = (num % 10) + '0';
}

char		*calc_ltoa(long long num)
{
	int		str_size;
	char	*new_str;
	short	sign;

	sign = (num < 0) ? -1 : 1;
	num *= sign;
	str_size = calc_digit(num);
	if (sign == -1)
		str_size++;
	if (!(new_str = (char *)malloc(sizeof(char) * (str_size + 1))))
		return (NULL);
	new_str[str_size] = '\0';
	if (sign == -1)
		new_str[0] = '-';
	calc_ltoa_rec(num, new_str, str_size - 1);
	return (new_str);
}
