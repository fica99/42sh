/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:08:14 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/27 18:47:33 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	k_bcsp(t_line *line)
{
	t_cord	*cord;

	cord = line->cord;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	if (is_start_pos(cord))
		return ;
	go_left(1, cord);
	del_symb(line->buffer.buffer, cord);
}

void	k_del(t_line *line)
{
	t_cord	*cord;

	cord = line->cord;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	if (is_end_pos(cord))
		return ;
	del_symb(line->buffer.buffer, cord);
}

void	k_home(t_line *line)
{
	t_cord	*cord;

	cord = line->cord;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	if (is_start_pos(cord))
		return ;
	go_left(cord->pos, cord);
}

void	k_end(t_line *line)
{
	t_cord	*cord;

	cord = line->cord;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	if (is_end_pos(cord))
		return ;
	go_right(ft_strlen(line->buffer.buffer + cord->pos), cord);
}

void	k_ctrl_up(t_line *line)
{
	short	len;
	t_cord	*cord;

	cord = line->cord;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start) *
	cord->ws_col);
	if (len - cord->ws_col < 0)
		return ;
	go_left(cord->ws_col, cord);
}
