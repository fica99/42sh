/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:54:59 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/28 20:53:29 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	k_ctrl_r(t_line *line)
{
	t_cord	*cord;

	cord = line->cord;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	if (!g_history.hist_len)
		return ;
	go_right(cord->x_end - cord->x_cur + ((cord->y_end - cord->y_cur) *
	cord->ws_col), cord);
	ft_putchar_fd(NEW_LINE, STDIN_FILENO);
	if (cord->y_cur >= cord->ws_row - 1)
		(cord->y_start)--;
	else
		(cord->y_cur)++;
	cord->x_cur = 0;
	ft_putstr_cord("bck-i-search: ", cord);
	ft_putstr_cord(line->history_search.buffer, cord);
	g_line_flags |= HISTORY_SEARCH;
}
