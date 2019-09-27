/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cur_movements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 13:41:01 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/27 14:04:27 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		go_to_cord(short x, short y, int fd)
{
	char	*cursor;

	cursor = SET_CUR;
	ft_putstr_fd(tparm(cursor, y, x), fd);
}

void		go_left(short i, t_cord *cord)
{
	if (i <= 0)
		return ;
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
	if (i <= 0)
		return ;
	cord->pos += i;
	cord->x_cur += i;
	while (cord->x_cur >= cord->ws_col)
	{
		cord->x_cur -= cord->ws_col;
		cord->y_cur++;
	}
	go_to_cord(cord->x_cur, cord->y_cur, STDIN_FILENO);
}
