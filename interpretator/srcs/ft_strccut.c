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

char *ft_strccut(char *str, char c)
{
	char *tmp;

	if (!str)
		return (0);
	while ((tmp = ft_strchr(str, c)))
		ft_stricut(str, tmp - str);
	return (str);
}
