/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:48:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/28 17:17:55 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	k_ctrl_down(t_line *line)
{
	short	len;
	t_cord	*cord;

	cord = line->cord;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
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
	if (is_start_pos(cord))
		return ;
	i = cord->pos;
	buf = line->buffer.buffer;
	while (--i >= 0)
	{
		if ((i == 0 || buf[i - 1] == ' ' || buf[i - 1] == '\n') &&
		ft_isalnum(buf[i]))
		{
			go_left(cord->pos - i, cord);
			break ;
		}
	}
}

void	k_ctrl_right(t_line *line)
{
	short	i;
	t_cord	*cord;
	char	*buf;

	cord = line->cord;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	if (is_end_pos(cord))
		return ;
	i = cord->pos;
	buf = line->buffer.buffer;
	while (buf[i])
	{
		if ((buf[i] == ' ' || buf[i] == '\n') && ft_isalnum(buf[i + 1]))
		{
			i++;
			break;
		}
		i++;
	}
	go_right(i - cord->pos, cord);
}

void	k_shift_left(t_line *line)
{
	t_cord	*cord;
	short	start;
	short	end;

	cord = line->cord;
	if (is_start_pos(cord))
		return ;
	if (!(g_line_flags & HIGHLIGHT_TEXT))
		cord->highlight_pos = cord->pos;
	start = cord->pos - 1;
	end = cord->highlight_pos;
	if (end < start)
	{
		start = end;
		end = cord->pos - 1;
	}
	ft_putstr_highlight(line->buffer.buffer, start, end, cord);
	go_left(1, cord);
}

void	k_shift_right(t_line *line)
{
	t_cord	*cord;
	short	start;
	short	end;

	cord = line->cord;
	if (is_end_pos(cord))
		return ;
	if (!(g_line_flags & HIGHLIGHT_TEXT))
		cord->highlight_pos = cord->pos;
	start = cord->highlight_pos;
	end = cord->pos + 1;
	if (end < start)
	{
		end = start;
		start = cord->pos + 1;
	}
	ft_putstr_highlight(line->buffer.buffer, start, end, cord);
	go_right(1, cord);
}
