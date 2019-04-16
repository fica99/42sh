/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:56:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/16 23:17:40 by filip            ###   ########.fr       */
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

void			check_cord(char *buf)
{
	int	i;

	i = cord.ws_col;
	if (cord.x_cur > cord.ws_col)
	{
		buf = buf;
		cord.x_cur = 1;
		(cord.y_cur)++;
		ft_putstr(DOWN);
		while(--i)
			ft_putstr(LEFT);
	}
	else if (cord.x_cur < 0)
	{
		(cord.y_cur)--;
		cord.x_cur = cord.ws_col - 1;
		ft_putstr(UP);
		while (--i)
			ft_putstr(RIGHT);
	}
}

void			check_key(char *c, char *buf, int len)
{
	if (*c == BCSP && len)
	{
		buf = ft_strdel_el(buf, --len);
		ft_putstr(LEFT);
		ft_putstr(buf + len);
		ft_putchar(' ');
		(cord.x_cur)--;
		len = ft_strlen(buf + len) + 1;
		while (len--)
			ft_putstr(LEFT);
	}
	else if (ft_isprint(*c) && *c != BCSP)
	{
		buf = ft_stradd(buf, c, len);
		ft_putstr(buf + len);
		cord.x_cur += ft_strlen(c);
		len = ft_strlen(buf + len) - 1;
		while (len--)
			ft_putstr(LEFT);
	}
}
