/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 15:50:44 by aashara-          #+#    #+#             */
/*   Updated: 2018/11/25 16:52:44 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*arr;
	size_t			i;

	arr = (unsigned char*)malloc(sizeof(unsigned char) * size);
	i = 0;
	if (!arr)
		return (NULL);
	while (i < size)
	{
		arr[i] = 0;
		i++;
	}
	arr[size] = '\0';
	return (arr);
}
