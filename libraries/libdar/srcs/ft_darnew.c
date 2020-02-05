/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:13:35 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/11 17:20:22 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdar.h"

char		**ft_darnew(size_t size)
{
	char	**arr;
	size_t	i;

	if (!(arr = (char**)malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	i = -1;
	while (++i <= size)
		arr[i] = NULL;
	return (arr);
}
