/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_paste.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 16:09:40 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/24 16:35:28 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		copy_highlight(t_buff *buffer, t_cord *cord)
{
	ft_memdel((void**)&(buffer->copy_buff));
	buffer->copy_malloc_len = buffer->malloc_len;
	if (!(buffer->copy_buff = ft_strnew(buffer->copy_malloc_len)))
	{
		reset_input_mode(&g_term.savetty);
		ft_putchar_fd('\n', STDERR_FILENO);
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	}
	if ((cord->pos - cord->highlight_pos) >= 0)
		buffer->copy_buff = copy_from_buff(buffer->buffer, buffer->copy_buff,
		cord->highlight_pos, cord->pos);
	else
		buffer->copy_buff = copy_from_buff(buffer->buffer, buffer->copy_buff,
		cord->pos, cord->highlight_pos);
}

void		paste_highlight(t_buff *buffer, t_cord *cord)
{
	short	position;
	short	len;

	while (ft_strlen(buffer->buffer) + ft_strlen(buffer->copy_buff) >=
				(unsigned)buffer->malloc_len)
			buffer->buffer = strnew_realloc_buf(buffer->buffer,
					buffer->malloc_len += NORMAL_LINE);
	buffer->buffer = ft_stradd(buffer->buffer, buffer->copy_buff, cord->pos);
	cord->highlight_pos = 0;
	position = cord->pos;
	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start)
		* cord->ws_col);
	go_left(len, cord);
	ft_putstr_cord(buffer->buffer, cord);
	go_left(cord->pos - position, cord);
}

void    cut_highlight(t_buff *buffer, t_cord *cord)
{
	short			pos;
	short           j;
	short			len;

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
	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start)
			* cord->ws_col);
	go_left(len, cord);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	ft_putstr_cord(buffer->buffer, cord);
	((pos - cord->highlight_pos) < 0) ? go_left(ft_strlen(buffer->buffer) - pos, cord) :
	go_left(ft_strlen(buffer->buffer) - cord->highlight_pos, cord);
	cord->highlight_pos = 0;
}

char	*cut_copy_paste(char *c, t_buff *buffer, t_cord *cord)
{
	if (!cord->highlight_pos && !(g_flags & START_POS))
		cord->highlight_pos = cord->pos;
	if (!cord->highlight_pos)
		g_flags |= START_POS;
	if (!ft_strcmp(c, tigetstr("kLFT")) && !is_start_pos(cord))
		highlight_left(buffer, cord);
	else if (!ft_strcmp(c, tigetstr("kRIT")) &&
	((short)ft_strlen(buffer->buffer) > cord->pos))
		highlight_right(buffer, cord);
	else if (*c == CTRL_C && (g_flags & TERM_HIGHLIGHT))
		copy_highlight(buffer, cord);
	else if (*c == CTRL_V && buffer->copy_buff)
		paste_highlight(buffer, cord);
	else if (*c == CTRL_X)
	{
		copy_highlight(buffer, cord);
		cut_highlight(buffer, cord);
	}
	else
		return (NULL);
	return (SOMETHING);
}
