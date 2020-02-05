/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dar_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:24:23 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/25 17:45:09 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdar.h"

void	ft_dar_sort(char **res)
{
	size_t	i;
	char	*tmp;

	if (!res || !*res)
		return ;
	i = 0;
	while (res[i + 1])
	{
		if (ft_strcmp(res[i], res[i + 1]) > 0)
		{
			tmp = res[i];
			res[i] = res[i + 1];
			res[i + 1] = tmp;
			if (i != 0)
				--i;
			continue ;
		}
		++i;
	}
}
