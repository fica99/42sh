/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:44:33 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/18 20:49:54 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	init_line(t_line *line, t_term *term)
{
	line->templates = init_templates();
	line->cord = init_cord();
	init_buff(&line->copy_buff);
	init_buff(&line->buffer);
	init_buff(&line->history_search);
	init_buff(&line->save_buff);
	init_buff(&line->stop_buff);
	line->history = term->history;
	line->history.history_index = ft_darlen(line->history.history_buff);
}

void	init_buff(t_buff *buffer)
{
	if (!(buffer->buffer = ft_strnew(NORMAL_LINE)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	buffer->malloc_len = NORMAL_LINE;
}

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
