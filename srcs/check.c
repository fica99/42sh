/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:56:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/13 15:24:27 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned short	double_arr_len(char **arr)
{
	unsigned short	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char			*check_path(void)
{
	char	*path;

	path = ft_strrchr(ft_getenv("PWD"), '/');
	ft_isprint(*(path + 1)) == 1 ? path = path + 1 : path;
	!ft_strcmp(ft_getenv("PWD"), ft_getenv("HOME")) ? path = "~" : path;
	return (path);
}

void			check_key(char *c, char *buf)
{
	if (!(ft_strcmp(c, LEFT)) && cord.x_cur > cord.prompt)
	{
		ft_putstr(LEFT);
		(cord.x_cur)--;
	}
	if (!(ft_strcmp(c, RIGHT)) && (cord.prompt + (short)ft_strlen(buf) >
				cord.x_cur))
		{
		ft_putstr(RIGHT);
		cord.x_cur++;
	}
}
