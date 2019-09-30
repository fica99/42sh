/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_cur_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:13:53 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/30 21:21:16 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	k_left(t_line *line)
{
	t_cord	*cord;

	cord = line->cord;
	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	if (is_start_pos(cord))
		return ;
	go_left(1, cord);
}

void	k_right(t_line *line)
{
	t_cord	*cord;

	cord = line->cord;
	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	if (is_end_pos(cord))
		return ;
	go_right(1, cord);
}

void	k_home(t_line *line)
{
	t_cord	*cord;

	cord = line->cord;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
	if (is_start_pos(cord))
		return ;
	go_left(cord->pos, cord);
}

void	k_end(t_line *line)
{
	t_cord	*cord;
	short	len;

	cord = line->cord;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
	if (is_end_pos(cord))
		return ;
	len = cord->x_end - cord->x_cur + ((cord->y_end - cord->y_cur) *
	cord->ws_col);
	go_right(len, cord);
}
