/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:29:29 by filip             #+#    #+#             */
/*   Updated: 2019/06/23 14:05:58 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		print_symb(char *c, char *buf, t_cord *cord)
{
	short	pos;

	buf = ft_stradd(buf, c, cord->pos);
	if (*c == '\n')
	{
		cord->pos++;
		return ;
	}
	pos = cord->pos;
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	ft_putstr_cord(buf + cord->pos, cord);
	go_left(cord->pos - pos, cord);
	go_right(ft_strlen(c), cord);
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
	if (!(symb = ft_strnew(1)))
	{
		reset_input_mode(&g_term.savetty);
		ft_putchar_fd('\n', STDERR_FILENO);
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	}
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

void		highlight_left(t_buff *buffer, t_cord *cord)
{

	short	position;
	short	len;

	position = cord->pos;
	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start) * cord->ws_col);
	g_flags |= TERM_HIGHLIGHT;
	go_left(len, cord);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	if (cord->highlight_pos >= position - 1)
		ft_putstr_highlight(buffer->buffer + cord->pos, position - 1 - cord->pos,  cord->highlight_pos - cord->pos, cord);
	else
		ft_putstr_highlight(buffer->buffer + cord->pos, cord->highlight_pos - cord->pos,  position - 1 - cord->pos, cord);
	go_left(cord->pos - (position - 1), cord);
}
