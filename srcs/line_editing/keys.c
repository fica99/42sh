/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:13:53 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/28 20:57:21 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	k_left(t_line *line)
{
	t_cord	*cord;

	cord = line->cord;
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
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	if (is_end_pos(cord))
		return ;
	go_right(1, cord);
}

void	k_ctrl_d(t_line *line)
{
	char	*buf;

	buf = line->buffer.buffer;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(buf, line->cord);
	if (*buf == '\0')
	{
		ft_strcat(buf, "exit");
		ft_putstr_cord(buf, line->cord);
		g_line_flags |= BREAK_FLAG;
	}
	else
		k_del(line);
}

void	k_ctrl_c(t_line *line)
{
	short	start;
	short	end;

	if (!(g_line_flags & HIGHLIGHT_TEXT))
	{
		ft_strclr(line->buffer.buffer);
		g_line_flags |= BREAK_FLAG;
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
		ft_strclr(line->copy_buff.buffer);
		while (end - start >= line->copy_buff.malloc_len)
			line->copy_buff.buffer = ft_strdup_realloc(line->copy_buff.buffer,
			line->copy_buff.malloc_len += NORMAL_LINE);
		ft_strncat(line->copy_buff.buffer, line->buffer.buffer + start,
		end - start);
	}
}

void	k_enter(t_line *line)
{
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, line->cord);
	check_quotes(line);
}
