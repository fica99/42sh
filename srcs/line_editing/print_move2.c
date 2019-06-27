/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_move2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:18:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/27 15:21:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

short	check_nl_left(t_cord *cord, short i)
{
	short	x;
	short	y;
	t_cord	*new_line;

	x = cord->x_cur;
	y = cord->y_cur;
	cord->x_cur -= i;
	while (cord->x_cur < 0)
	{
		cord->x_cur += cord->ws_col;
		cord->y_cur--;
	}
	new_line = cord;
	while ((new_line = new_line->nl))
	{
		if (cord->x_cur > new_line->x_cur && (cord->y_start + new_line->y_cur) == cord->y_cur)
			break;
	}
	cord->x_cur = x;
	cord->y_cur = y;
	if (new_line)
		i = (cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start) * cord->ws_col)) -
		(new_line->x_cur - cord->x_start + new_line->y_cur * cord->ws_col);
	return (i);
}

short	check_nl_right(t_cord *cord, short i)
{
	short	x;
	short	y;
	t_cord	*new_line;

	x = cord->x_cur;
	y = cord->y_cur;
	cord->x_cur += i;
	while (cord->x_cur >= cord->ws_col)
	{
		cord->x_cur -= cord->ws_col;
		cord->y_cur++;
	}
	new_line = cord;
	while ((new_line = new_line->nl))
	{
		if (cord->x_cur > new_line->x_cur && (cord->y_start + new_line->y_cur) == cord->y_cur)
			break;
	}
	cord->x_cur = x;
	cord->y_cur = y;
	if (new_line)
		i = cord->ws_col - cord->x_cur;
	return (i);
}

