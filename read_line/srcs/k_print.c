/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:54:59 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/23 16:59:05 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	k_ctrl_d(t_line *line)
{
	char	*buf;

	buf = line->buffer.buffer;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(buf, line->cord);
	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
	if (is_end_pos(line->cord))
	{
		if (*buf == '\0')
		{
			ft_strcpy(buf, "exit");
			ft_putstr_cord(buf, line->cord);
		}
		k_enter(line);
	}
	else
		k_del(line);
}

void	k_enter(t_line *line)
{
	t_cord	*cord;

	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, line->cord);
	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
	cord = line->cord;
	go_right(cord->x_end - cord->x_cur + ((cord->y_end - cord->y_cur) *
	cord->ws_col), cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putchar_fd(NEW_LINE, STDIN_FILENO);
	check_end_window(cord);
	g_line_flags |= BREAK_FLAG;
}

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
	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
	if (is_end_pos(cord))
		return ;
	del_symb(line->buffer.buffer, cord);
}

void	k_tab(t_line *line)
{
	char	*word;
	char	is_command;

	word = ac_get_word(&is_command, line->buffer.buffer, line->cord->pos);
	if (is_command)
		ac_bins(word, line);
	else
		ac_path(word, line);
	ft_strdel(&word);
}
