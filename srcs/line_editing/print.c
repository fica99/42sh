/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:32:00 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/27 19:26:53 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_putstr_cord(char *str, t_cord *cord)
{
	while (str && *str)
	{
		ft_putchar_fd(*str, STDIN_FILENO);
		if (++cord->x_cur >= cord->ws_col)
		{
			ft_putchar_fd(NEW_LINE, STDIN_FILENO);
			cord->x_cur = 0;
			if (cord->y_cur >= cord->ws_row - 1)
				(cord->y_start)--;
			else
				(cord->y_cur)++;
		}
		str++;
		cord->pos++;
	}
	set_end_cord(cord);
}

void		ft_putstr_highlight(char *str, short start, short end, t_cord *cord)
{
	short	i;
	char	symb[2];

	i = -1;
	if (start <= i)
		HIGHLIGHT(STDIN_FILENO);
	symb[1] = '\0';
	while (str[++i])
	{
		if (i == start)
			HIGHLIGHT(STDIN_FILENO);
		symb[0] = str[i];
		ft_putstr_cord(symb, cord);
		if (i == end)
			STANDART(STDIN_FILENO);
	}
	STANDART(STDIN_FILENO);
}

void		disable_highlight(char *buffer, t_cord *cord)
{
	short	pos;

	g_line_flags &= ~HIGHLIGHT_TEXT;
	pos = cord->pos;
	go_left(pos, cord);
	ft_putstr_cord(buffer + cord->pos, cord);
	go_left(cord->pos - pos, cord);
	cord->highlight_pos = 0;
}
