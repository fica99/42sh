/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_cur_movements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:13:53 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/30 18:46:23 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_left(t_readline *line)
{
	// if (g_line_flags & HISTORY_SEARCH)
	// 	disable_history(line);
	// if (g_line_flags & HIGHLIGHT_TEXT)
	// 	disable_highlight(line->buffer.buffer, cord);
	 if (rl_is_start_pos(&line->cord))
		return ;
	rl_go_left(1, &line->cord);
}

void	rl_k_right(t_readline *rl)
{
	// if (g_line_flags & HISTORY_SEARCH)
	// 	disable_history(line);
	// if (g_line_flags & HIGHLIGHT_TEXT)
	// 	disable_highlight(line->buffer.buffer, cord);
	if (rl_is_end_pos(&rl->cord))
		return ;
	rl_go_right(1, &rl->cord);
}

void	rl_k_home(t_readline *rl)
{
	// if (g_line_flags & HIGHLIGHT_TEXT)
	// 	disable_highlight(line->buffer.buffer, cord);
	// if (g_line_flags & HISTORY_SEARCH)
	// 	disable_history(line);
	if (rl_is_start_pos(&rl->cord))
		return ;
	rl_go_left(rl->cord.pos, &rl->cord);
}

void	rl_k_end(t_readline *rl)
{
	short		len;
	t_rl_cord	cord;

	// if (g_line_flags & HIGHLIGHT_TEXT)
	// 	disable_highlight(line->buffer.buffer, cord);
	// if (g_line_flags & HISTORY_SEARCH)
	// 	disable_history(line);
	if (rl_is_end_pos(&rl->cord))
		return ;
	cord = rl->cord;
	len = cord.x_end - cord.x_cur + ((cord.y_end - cord.y_cur) *
	cord.ws_col);
	rl_go_right(len, &rl->cord);
}
