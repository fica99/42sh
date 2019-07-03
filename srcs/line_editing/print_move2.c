/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_move2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:18:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/07/03 14:26:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	check_nl_left(t_cord *cord, short i)
{
	t_cord	*new_line;

	cord->x_cur -= i;
	while (cord->x_cur < 0)
	{
		cord->x_cur += cord->ws_col;
		cord->y_cur--;
		new_line = cord->nl;
		while (new_line)
		{
			if ((cord->y_start + new_line->y_cur) == cord->y_cur)
			{
				cord->x_cur -= cord->ws_col - new_line->x_cur - 1;
				break ;
			}
			new_line = new_line->nl;
		}
	}
}

void	check_nl_right(t_cord *cord, short i)
{
	t_cord	*new_line;

	cord->x_cur += i;
	new_line = cord->nl;
	while (new_line)
	{
		if ((cord->y_start + new_line->y_cur) == cord->y_cur && cord->x_cur >
		new_line->x_cur)
		{
			i = cord->x_cur - new_line->x_cur - 1;
			cord->x_cur = 0;
			cord->y_cur++;
			check_nl_right(cord, i);
		}
		new_line = new_line->nl;
	}
	while (cord->x_cur >= cord->ws_col)
	{
		cord->x_cur -= cord->ws_col;
		cord->y_cur++;
	}
}
