/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   highlight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 19:35:43 by filip             #+#    #+#             */
/*   Updated: 2019/07/03 14:28:59 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		disable_highlight(t_cord *cord, char *buffer)
{
	short	pos;

	if (g_flags & TERM_HIGHLIGHT)
	{
		g_flags &= ~TERM_HIGHLIGHT;
		if (g_flags & START_POS)
			g_flags &= ~START_POS;
		cord->highlight_pos = 0;
		pos = cord->pos;
		go_left(cord->pos, cord);
		ft_putstr_cord(buffer + cord->pos, cord);
		go_left(cord->pos - pos, cord);
	}
}

void		highlight_left(char *buffer, t_cord *cord)
{
	short	position;

	position = cord->pos;
	g_flags |= TERM_HIGHLIGHT;
	go_left(cord->pos, cord);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	if (cord->highlight_pos >= position - 1)
		ft_putstr_highlight(buffer + cord->pos, position - 1 - cord->pos,
		cord->highlight_pos - cord->pos, cord);
	else
		ft_putstr_highlight(buffer + cord->pos, cord->highlight_pos - cord->pos,
		position - 1 - cord->pos, cord);
	go_left(cord->pos - (position - 1), cord);
}

void		highlight_right(char *buffer, t_cord *cord)
{
	short	position;

	position = cord->pos;
	g_flags |= TERM_HIGHLIGHT;
	go_left(cord->pos, cord);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	if (cord->highlight_pos >= position + 1)
		ft_putstr_highlight(buffer + cord->pos, position + 1 - cord->pos,
		cord->highlight_pos - cord->pos, cord);
	else
		ft_putstr_highlight(buffer + cord->pos, cord->highlight_pos - cord->pos,
		position + 1 - cord->pos, cord);
	go_left(cord->pos - (position + 1), cord);
}

void		ft_putstr_highlight(char *str, short start, short end, t_cord *cord)
{
	short	i;
	char	*symb;

	i = -1;
	if (!(symb = ft_strnew(1)))
	{
		go_right(ft_strlen(g_line.buffer.buffer) - cord->pos, cord);
		reset_input_mode(&g_line.savetty);
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
