/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:18:04 by filip             #+#    #+#             */
/*   Updated: 2019/09/19 21:34:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_cord	*init_cord(void)
{
	t_cord	*cord;

	if (!(cord = (t_cord*)malloc(sizeof(t_cord))))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	cord->nl = NULL;
	cord->x_cur = 0;
	cord->x_start = 0;
	cord->ws_col = 0;
	cord->ws_row = 0;
	cord->y_cur = 0;
	cord->y_start = 0;
	cord->pos = 0;
	cord->highlight_pos = 0;
	return (cord);
}

void	set_start_cord(t_cord *cord)
{
	cord->x_start = cord->x_cur;
	cord->y_start = cord->y_cur;
}

void	init_buff(t_buff *buffer)
{
	if (!(buffer->buffer = ft_strnew(NORMAL_LINE)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	buffer->malloc_len = NORMAL_LINE;
}

void	init_line(t_line *line, t_term *term)
{
	g_line_flags = INIT_FLAGS;
	line->copy_buff.buffer = term->copy_line;
	line->copy_buff.malloc_len = ft_strlen(term->copy_line);
	line->cord = init_cord();
	get_win_size(line->cord);
	get_cur_cord(line->cord);
	set_start_cord(line->cord);
	init_buff(&line->buffer);
	init_buff(&line->history_search);
	init_buff(&line->save_buff);
	init_buff(&line->stop_buff);
	line->history = term->history;
	line->history.history_index = ft_darlen(line->history.history_buff);
}

void	check_malloc_len_buffer(t_buff *buffer, char *c)
{
	while (ft_strlen(buffer->buffer) + ft_strlen(c) >=
			(unsigned)buffer->malloc_len)
		buffer->buffer = ft_strdup_realloc(buffer->buffer,
		buffer->malloc_len += NORMAL_LINE);
}
