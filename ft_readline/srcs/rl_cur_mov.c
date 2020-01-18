/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_cur_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:50:40 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/08 14:51:38 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void		rl_go_to_cord(short x, short y)
{
	ft_putstr(tparm(RL_SET_CUR, y, x));
}

void		rl_go_left(short i, t_rl_cord *cord)
{
	short	len;

	if (i <= 0)
		return ;
	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start) *
	cord->ws_col);
	if (i > len)
		i = len;
	if (i > cord->pos)
		i = cord->pos;
	cord->pos -= i;
	cord->x_cur -= i;
	while (cord->x_cur < 0)
	{
		cord->x_cur += cord->ws_col;
		cord->y_cur--;
	}
	rl_go_to_cord(cord->x_cur, cord->y_cur);
}

void		rl_go_right(short i, t_rl_cord *cord)
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
	rl_go_to_cord(cord->x_cur, cord->y_cur);
}
