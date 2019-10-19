/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_cur_movements2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:08:14 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/19 18:14:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

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

void	k_ctrl_down(t_line *line)
{
	short	len;
	t_cord	*cord;

	cord = line->cord;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
	len = cord->x_end - cord->x_cur + ((cord->y_end - cord->y_cur) *
	cord->ws_col);
	if (len - cord->ws_col < 0)
		return ;
	go_right(cord->ws_col, cord);
}

void	k_ctrl_left(t_line *line)
{
	t_cord	*cord;
	short	i;
	char	*buf;

	cord = line->cord;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
	if (is_start_pos(cord))
		return ;
	i = cord->pos;
	buf = line->buffer.buffer;
	while (--i > 0)
	{
		if (ft_isspace(buf[i - 1]) && ft_isalnum(buf[i]))
			break ;
	}
	go_left(cord->pos - i, cord);
}

void	k_ctrl_right(t_line *line)
{
	short	i;
	t_cord	*cord;
	char	*buf;

	cord = line->cord;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
	if (is_end_pos(cord))
		return ;
	i = cord->pos;
	buf = line->buffer.buffer;
	while (buf[i])
	{
		if (ft_isspace(buf[i]) && ft_isalnum(buf[i + 1]))
		{
			i++;
			break;
		}
		i++;
	}
	go_right(i - cord->pos, cord);
}
