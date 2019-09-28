/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 20:16:36 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/28 15:46:41 by aashara-         ###   ########.fr       */
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

void	k_up(t_line *line)
{
	t_cord	*cord;

	if ((!line->history_index))
		return ;
	cord = line->cord;
	go_left(cord->pos, cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	if (line->history_index == g_history.hist_len)
	{
		check_malloc_len_buffer(&line->save_buff, line->buffer.buffer + cord->pos);
		ft_strcat(line->save_buff.buffer, line->buffer.buffer + cord->pos);
	}
	--(line->history_index);
	ft_strclr(line->buffer.buffer + cord->pos);
	check_malloc_len_buffer(&line->buffer,
	g_history.history_buff[line->history_index]);
	ft_strcat(line->buffer.buffer, g_history.history_buff[(line->history_index)]);
	ft_putstr_cord(line->buffer.buffer + cord->pos, cord);
}

void	k_down(t_line *line)
{
	char	*history_buffer;
	t_cord	*cord;

	if (line->history_index == g_history.hist_len)
		return ;
	cord = line->cord;
	go_left(cord->pos, cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	++(line->history_index);
	if (line->history_index == g_history.hist_len)
		history_buffer = line->save_buff.buffer;
	else
		history_buffer = g_history.history_buff[(line->history_index)];
	ft_strclr(line->buffer.buffer + cord->pos);
	check_malloc_len_buffer(&line->buffer, history_buffer);
	ft_strcat(line->buffer.buffer, history_buffer);
	ft_putstr_cord(line->buffer.buffer + cord->pos, cord);
	if (line->history_index == g_history.hist_len)
		ft_strclr(line->save_buff.buffer);
}
