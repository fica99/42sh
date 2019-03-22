/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 19:44:35 by aashara-          #+#    #+#             */
/*   Updated: 2018/11/24 17:43:27 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *destination, const char *source, size_t n)
{
	char	*pointer1;
	int		i;
	int		len;

	pointer1 = destination;
	i = 0;
	len = n;
	if (len == 0)
		return (pointer1);
	while (source[i] != '\0' && i < len)
	{
		pointer1[i] = source[i];
		i++;
	}
	while (i < len)
	{
		pointer1[i] = '\0';
		i++;
	}
	return (pointer1);
}
