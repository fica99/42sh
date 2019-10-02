/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_highlight.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:48:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/02 15:29:27 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	k_shift_left(t_line *line)
{
	t_cord	*cord;
	short	start;
	short	end;

	cord = line->cord;
	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
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
	ft_putstr_fd(SAVE_CUR, STDIN_FILENO);
	ft_putstr_highlight(line->buffer.buffer, start, end, cord);
	ft_putstr_fd(RESTORE_CUR, STDIN_FILENO);
	go_left(1, cord);
}

void	k_shift_right(t_line *line)
{
	t_cord	*cord;
	short	start;
	short	end;

	cord = line->cord;
	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
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
	ft_putstr_fd(SAVE_CUR, STDIN_FILENO);
	ft_putstr_highlight(line->buffer.buffer, start, end, cord);
	ft_putstr_fd(RESTORE_CUR, STDIN_FILENO);
	go_right(1, cord);
}

void	k_ctrl_c(t_line *line)
{
	short	start;
	short	end;

	if (!(g_line_flags & HIGHLIGHT_TEXT))
	{
		ft_strclr(line->buffer.buffer);
		g_flags |= BREAK_FLAG;
	}
	else
	{
		start = line->cord->pos;
		end = line->cord->highlight_pos;
		if (end < start)
		{
			start = end;
			end = line->cord->pos;
		}
		while (end - start >= line->copy_buff.malloc_len)
			line->copy_buff.buffer = ft_strdup_realloc(line->copy_buff.buffer,
			line->copy_buff.malloc_len += NORMAL_LINE);
		ft_strncpy(line->copy_buff.buffer, line->buffer.buffer + start,
		end - start);
	}
}

void	k_ctrl_x(t_line *line)
{
	t_cord	*cord;
	short	start;
	short	end;
	short	j;

	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
	if (!(g_line_flags & HIGHLIGHT_TEXT))
		return ;
	k_ctrl_c(line);
	cord = line->cord;
	start = cord->highlight_pos;
	end = cord->pos;
	j = start;
	if (end < start)
	{
		start = end;
		end = j;
		j = start;
	}
	while (++j <= end)
		line->buffer.buffer = ft_strdel_el(line->buffer.buffer, start);
	disable_highlight(line->buffer.buffer, cord);
}

void	k_ctrl_v(t_line *line)
{
	char	*buff;
	t_cord	*cord;

	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
	check_malloc_len_buffer(&line->buffer, line->copy_buff.buffer);
	buff = line->buffer.buffer;
	cord =line->cord;
	buff = ft_stradd(buff, line->copy_buff.buffer, cord->pos);
	disable_highlight(buff, cord);
}
