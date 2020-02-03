/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dar2str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 15:30:02 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/24 19:56:52 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdar.h"

char	*ft_dar2str(char **arr, char *symb)
{
	int		i;
	char	*res;
	char	*line;

	if (!arr)
		return (NULL);
	i = -1;
	line = "";
	while (arr[++i])
	{
		if (symb)
			res = ft_strjoin(arr[i], symb);
		else
			res = ft_strdup(arr[i]);
		if (!res)
			return (NULL);
		line = ft_strjoin(line, res);
		ft_strdel(&res);
	}
	return (line);
}
