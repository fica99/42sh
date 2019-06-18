/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 19:35:43 by filip             #+#    #+#             */
/*   Updated: 2019/06/17 16:08:03 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_shell.h"

void		highlight_right(t_buff *buffer, t_cord *cord, short pos)
{
    short			len;

	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start)
	* cord->ws_col);
	g_flags |= TERM_HIGHLIGHT;
	go_left(len, cord);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	if (pos >= len + 1)
		ft_putstr_highlight(buffer->buffer, len + 1,  pos, cord);
	else
		ft_putstr_highlight(buffer->buffer, pos,  len + 1, cord);
	go_left(ft_strlen(buffer->buffer) - (len + 1), cord);
}

void		disable_highlight(t_cord *cord, t_buff *buffer, short len)
{
	if (g_flags & TERM_HIGHLIGHT)
	{
		g_flags &= ~TERM_HIGHLIGHT;
		if (g_flags & START_POS)
			g_flags &= ~START_POS;
		cord->highlight_pos = 0;
		go_left(len, cord);
		ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
		ft_putstr_cord(buffer->buffer, cord);
		go_left(ft_strlen(buffer->buffer) - len, cord);
	}
}

void		copy_highlight(t_buff *buffer, t_cord *cord)
{
	short			len;

	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start)
	* cord->ws_col);
	ft_memdel((void**)&(buffer->copy_buff));
	buffer->copy_malloc_len = buffer->malloc_len;
	if (!(buffer->copy_buff = ft_strnew(buffer->copy_malloc_len)))
	{
		reset_input_mode(&g_term.savetty);
		ft_putchar_fd('\n', STDERR_FILENO);
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	}
	if ((len - cord->highlight_pos) >= 0)
		buffer->copy_buff = copy_from_buff(buffer->buffer, buffer->copy_buff,
		cord->highlight_pos, len);
	else
		buffer->copy_buff = copy_from_buff(buffer->buffer, buffer->copy_buff,
		len, cord->highlight_pos);
}

void		paste_highlight(t_buff *buffer, t_cord *cord)
{
	short	len;

	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start)
	* cord->ws_col);
	buffer->buffer = ft_stradd(buffer->buffer, buffer->copy_buff, len);
	cord->highlight_pos = 0;
	go_left(len, cord);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	ft_putstr_cord(buffer->buffer, cord);
	go_left(ft_strlen(buffer->buffer) - len, cord);
}

void    cut_highlight(t_buff *buffer, t_cord *cord)
{
	short			len;
	short           j;

	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start)
	* cord->ws_col);
	if ((len - cord->highlight_pos) >= 0)
	{
		j = cord->highlight_pos;
		while (j++ <= len)
			buffer->buffer = ft_strdel_el(buffer->buffer, cord->highlight_pos);
	}
	else
	{
		j = len;
		while (j++ <= cord->highlight_pos)
			buffer->buffer = ft_strdel_el(buffer->buffer, len);
	}
	go_left(len, cord);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	ft_putstr_cord(buffer->buffer, cord);
	if ((len - cord->highlight_pos) < 0)
		go_left(ft_strlen(buffer->buffer) - len, cord);
	else
		go_left(ft_strlen(buffer->buffer) - cord->highlight_pos, cord);
	cord->highlight_pos = 0;
}