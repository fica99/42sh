/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:26:08 by mmarti            #+#    #+#             */
/*   Updated: 2019/11/29 16:26:10 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

char *ft_stricut(char *str, int i)
{
	if (!str)
		return (0);
	if (i > (int)ft_strlen(str) - 1)
		return (str);
	str += i;
	while (*++str)
		*(str - 1) = *str;
	*(str - 1) = 0;
	return (str);
}

char *ft_strccut(char *str, char c)
{
	char *tmp;

	if (!str)
		return (0);
	while ((tmp = ft_strchr(str, c)))
		ft_stricut(str, tmp - str);
	return (str);
}
