/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:18:04 by filip             #+#    #+#             */
/*   Updated: 2019/07/03 15:35:19 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_cord	*init_cord(void)
{
	t_cord	*cord;

	if (!(cord = (t_cord*)malloc(sizeof(t_cord))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
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
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	buffer->malloc_len = NORMAL_LINE;
}

void	init_line(t_line *line)
{
	line->cord = init_cord();
	get_win_size(line->cord);
	get_cur_cord(line->cord, 1);
	set_start_cord(line->cord);
	init_buff(&line->buffer);
	init_buff(&line->history_search);
	init_buff(&line->save_buff);
}
