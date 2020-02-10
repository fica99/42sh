/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dar2str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara <aashara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 15:30:02 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/10 12:05:51 by aashara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdar.h"

char	*ft_dar2str(char **arr, char *symb)
{
	int		i;
	char	*res;
	char	*line;
	char	*tmp;

	if (!arr)
		return (NULL);
	i = -1;
	if (!(line = ft_strnew(1)))
		return (NULL);
	while (arr[++i])
	{
		if (symb)
			res = ft_strjoin(arr[i], symb);
		else
			res = ft_strdup(arr[i]);
		if (!res)
			return (NULL);
		tmp = ft_strjoin(line, res);
		ft_strdel(&line);
		ft_strdel(&res);
		line = tmp;
	}
	return (line);
}
