/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:54:59 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/29 19:40:01 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	k_ctrl_r(t_line *line)
{
	t_cord	*cord;

	cord = line->cord;
	if (!g_history.hist_len)
		return ;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	go_to_cord(cord->x_end, cord->y_end, STDIN_FILENO);
	ft_putchar_fd(NEW_LINE, STDIN_FILENO);
	if (cord->y_end >= cord->ws_row - 1)
	{
		--cord->y_cur;
		--cord->y_start;
		--cord->y_end;
	}
	ft_putstr_fd("bck-i-search: ", STDIN_FILENO);
	ft_putstr_fd(line->history_search.buffer, STDIN_FILENO);
	go_to_cord(cord->x_cur, cord->y_cur, STDIN_FILENO);
	g_line_flags |= HISTORY_SEARCH;
}
