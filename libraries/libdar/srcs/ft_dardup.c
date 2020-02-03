/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dardup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:19:52 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/11 17:19:53 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdar.h"

char		**ft_dardup(char **arr)
{
	short	i;
	char	**arr1;

	if (!arr)
		return (NULL);
	if (!(arr1 = (char**)malloc(sizeof(char*) * (ft_darlen(arr) + 1))))
		return (NULL);
	i = -1;
	while (arr[++i])
		if (!(arr1[i] = ft_strdup(arr[i])))
			return (NULL);
	arr1[i] = NULL;
	return (arr1);
}
