/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cur_movements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 13:41:01 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/18 19:45:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_shell.h"

void		go_to_cord(short x, short y, int fd)
{
	char	*cursor;

	cursor = SET_CUR;
	ft_putstr_fd(tparm(cursor, y, x), fd);
}

void		go_left(short i, t_cord *cord)
{
	short	len;

	if (i <= 0)
		return ;
	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start) *
	cord->ws_col);
	if (i > len)
		i = len;
	cord->pos -= i;
	cord->x_cur -= i;
	while (cord->x_cur < 0)
	{
		cord->x_cur += cord->ws_col;
		cord->y_cur--;
	}
	go_to_cord(cord->x_cur, cord->y_cur, STDIN_FILENO);
}

void		go_right(short i, t_cord *cord)
{
	short	len;

	if (i <= 0)
		return ;
	len = cord->x_end - cord->x_cur + ((cord->y_end - cord->y_cur) *
	cord->ws_col);
	if (i > len)
		i = len;
	cord->pos += i;
	cord->x_cur += i;
	while (cord->x_cur >= cord->ws_col)
	{
		cord->x_cur -= cord->ws_col;
		cord->y_cur++;
	}
	go_to_cord(cord->x_cur, cord->y_cur, STDIN_FILENO);
}
