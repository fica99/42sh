/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_paste.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 16:09:40 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/11 16:28:50 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		copy_highlight(t_buff *copy_buff, t_buff *buffer, t_cord *cord)
{
	ft_memdel((void**)&(copy_buff->buffer));
	copy_buff->malloc_len = buffer->malloc_len;
	if (!(copy_buff->buffer = ft_strnew(copy_buff->malloc_len)))
	{
		go_right(ft_strlen(g_line.buffer.buffer) - g_line.cord->pos,
		g_line.cord);
		ft_putchar_fd('\n', STDERR_FILENO);
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	}
	if ((cord->pos - cord->highlight_pos) >= 0)
		copy_buff->buffer = copy_from_buff(buffer->buffer, copy_buff->buffer,
		cord->highlight_pos, cord->pos);
	else
		copy_buff->buffer = copy_from_buff(buffer->buffer, copy_buff->buffer,
		cord->pos, cord->highlight_pos);
}

void		paste_highlight(t_buff *buffer, t_buff *copy_buff, t_cord *cord)
{
	short	position;

	check_malloc_len_buffer(buffer, copy_buff->buffer);
	buffer->buffer = ft_stradd(buffer->buffer, copy_buff->buffer, cord->pos);
	position = cord->pos;
	go_left(cord->pos, cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putstr_cord(buffer->buffer + cord->pos, cord);
	go_left(cord->pos - position, cord);
	disable_highlight(cord, buffer->buffer);
}

void		cut_highlight(t_buff *buffer, t_cord *cord)
{
	short	pos;
	short	j;

	pos = cord->pos;
	if ((cord->pos - cord->highlight_pos) >= 0)
	{
		j = cord->highlight_pos;
		while (j++ <= cord->pos)
			buffer->buffer = ft_strdel_el(buffer->buffer, cord->highlight_pos);
	}
	else
	{
		j = cord->pos;
		while (j++ <= cord->highlight_pos)
			buffer->buffer = ft_strdel_el(buffer->buffer, cord->pos);
	}
	go_left(cord->pos, cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putstr_cord(buffer->buffer + cord->pos, cord);
	((pos - cord->highlight_pos) < 0) ? go_left(ft_strlen(buffer->buffer) - pos,
	cord) : go_left(ft_strlen(buffer->buffer) - cord->highlight_pos, cord);
	disable_highlight(cord, buffer->buffer);
}

char		*cut_copy_paste(char *c, t_line *line)
{
	if (!line->cord->highlight_pos && !(g_line_flags & START_POS))
		line->cord->highlight_pos = line->cord->pos;
	if (!line->cord->highlight_pos)
		g_line_flags |= START_POS;
	if (!ft_strcmp(c, SHIFT_LFT) && !is_start_pos(line->cord))
		highlight_left(line->buffer.buffer, line->cord);
	else if (!ft_strcmp(c, SHIFT_RGHT) &&
	((short)ft_strlen(line->buffer.buffer) > line->cord->pos))
		highlight_right(line->buffer.buffer, line->cord);
	else if (*c == CTRL_C && (g_line_flags & TERM_HIGHLIGHT))
		copy_highlight(&line->copy_buff, &line->buffer, line->cord);
	else if (*c == CTRL_V && line->copy_buff.buffer)
		paste_highlight(&line->buffer, &line->copy_buff, line->cord);
	else if (*c == CTRL_X)
	{
		copy_highlight(&line->copy_buff, &line->buffer, line->cord);
		cut_highlight(&line->buffer, line->cord);
	}
	else
		return (NULL);
	return (SOMETHING);
}
