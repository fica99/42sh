/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 23:20:54 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/18 17:46:55 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdar.h"

char	**ft_darjoin(char **first, char **second)
{
	char	**res;
	int		i;
	int		j;

	res = NULL;
	if (first || second)
	{
		if (!(res = ft_darnew(ft_darlen(first) + ft_darlen(second))))
			return (NULL);
		i = -1;
		j = -1;
		while (first[++j])
			if (!(res[++i] = ft_strdup(first[j])))
				return (NULL);
		j = -1;
		while (second[++j])
			if (!(res[++i] = ft_strdup(second[j])))
				return (NULL);
	}
	return (res);
}
