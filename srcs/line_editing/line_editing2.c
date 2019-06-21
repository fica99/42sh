/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:29:29 by filip             #+#    #+#             */
/*   Updated: 2019/06/21 23:59:31 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		print_symb(char *c, char *buf, t_cord *cord)
{
	short	i;

	buf = ft_stradd(buf, c, cord->pos);
	if (*c == '\n')
		return ;
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	ft_putstr_cord(buf + cord->pos, cord);
	i = ft_strlen(buf + cord->pos) - 1;
	go_left(i, cord);
}

void		go_to_cord(short x, short y, int fd)
{
	char	*cursor;

	cursor = tigetstr("cup");
	ft_putstr_fd(tparm(cursor, y, x), fd);
}

void		ft_putstr_cord(char *str, t_cord *cord)
{
	while (str && *str)
	{
		ft_putchar_fd(*str, STDIN_FILENO);
		if (*str == '\n')
		{
			cord->x_cur = 0;
			if (cord->y_cur >= cord->ws_row - 1)
				(cord->y_start)--;
			else
				(cord->y_cur)++;
		}
		else
			(cord->x_cur)++;
		str++;
		if (cord->x_cur >= cord->ws_col)
		{
			ft_putchar_fd('\n', STDIN_FILENO);
			cord->x_cur = 0;
			if (cord->y_cur >= cord->ws_row - 1)
				(cord->y_start)--;
			else
				(cord->y_cur)++;
		}
		cord->pos++;
	}
}

void		ft_putstr_highlight(char *str, short start, short end, t_cord *cord)
{
	short	i;
	char	*symb;

	i = -1;
	symb = ft_strnew(1);
	if (start <= i)
		HIGHLIGHT(STDIN_FILENO);
	while (str[++i])
	{
		if (i == start)
			HIGHLIGHT(STDIN_FILENO);
		symb[0] = str[i];
		ft_putstr_cord(symb, cord);
		if (i == end)
			STANDART(STDIN_FILENO);
	}
	ft_memdel((void**)&symb);
	STANDART(STDIN_FILENO);
}

void		highlight_left(t_buff *buffer, t_cord *cord, short pos)
{
	g_flags |= TERM_HIGHLIGHT;
	go_left(cord->pos, cord);
	if (pos >= cord->pos - 1)
		ft_putstr_highlight(buffer->buffer, len - 1, pos, cord);
	else
		ft_putstr_highlight(buffer->buffer, pos,  len - 1, cord);
	go_left(ft_strlen(buffer->buffer) - (len - 1), cord);
}
