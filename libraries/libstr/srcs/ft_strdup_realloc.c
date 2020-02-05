/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_realloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:22:33 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/15 21:17:56 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

char	*ft_strdup_realloc(char *str, short len)
{
	char	*arr;

	arr = str;
	if (!(str = ft_strnew(len)))
		return (NULL);
	if (arr)
		str = ft_strcat(str, arr);
	ft_memdel((void**)&arr);
	return (str);
}
