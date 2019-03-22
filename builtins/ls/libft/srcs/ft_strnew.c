/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:27:35 by aashara-          #+#    #+#             */
/*   Updated: 2018/12/22 15:22:38 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*arr;

	if (size >= 9223372036854775807)
		return (NULL);
	arr = (char*)malloc(sizeof(char) * size + 1);
	if (!arr)
		return (NULL);
	arr[size] = '\0';
	while (size--)
		arr[size] = '\0';
	return (arr);
}
