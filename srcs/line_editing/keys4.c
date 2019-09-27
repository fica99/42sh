/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 20:16:36 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/27 22:40:20 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	k_ctrl_x(t_line *line)
{
	t_cord	*cord;
	short	start;
	short	end;
	short	j;

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

	check_malloc_len_buffer(&line->buffer, line->copy_buff.buffer);
	buff = line->buffer.buffer;
	cord =line->cord;
	buff = ft_stradd(buff, line->copy_buff.buffer, cord->pos);
	disable_highlight(buff, cord);
}
