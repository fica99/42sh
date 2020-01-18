/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_init_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 16:01:09 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/08 12:53:17 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void		rl_init_buff(t_buff *buffer)
{
	if (!(buffer->buffer = ft_strnew(LINE_SIZE)))
		rl_err("42sh", "malloc() error", ENOMEM);
	buffer->malloc_len = LINE_SIZE;
	buffer->cur_len = 0;
}

void		rl_init_cord(t_rl_cord *cord)
{
	cord->x_cur = 0;
	cord->x_start = 0;
	cord->ws_col = 0;
	cord->ws_row = 0;
	cord->y_cur = 0;
	cord->y_start = 0;
	cord->pos = 0;
	cord->highlight_pos = 0;
	cord->x_end = 0;
	cord->y_end = 0;
}
