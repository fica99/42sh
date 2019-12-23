/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_cur_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:08:14 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/18 13:33:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_right(t_readline *rl)
{
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	rl_go_right(1, &rl->cord);
}

void	rl_k_end(t_readline *rl)
{
	short		len;

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	len = rl->cord.x_end - rl->cord.x_cur + ((rl->cord.y_end - rl->cord.y_cur)
	* rl->cord.ws_col);
	rl_go_right(len, &rl->cord);
}

void	rl_k_ctrl_down(t_readline *rl)
{
	short		len;
	t_rl_cord	cord;

	cord = rl->cord;
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	len = cord.x_end - cord.x_cur + ((cord.y_end - cord.y_cur) *
	cord.ws_col);
	if (len - cord.ws_col < 0)
		return ;
	rl_go_right(rl->cord.ws_col, &rl->cord);
}

void	rl_k_ctrl_right(t_readline *rl)
{
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	rl_go_right(rl_next_word(rl->line.buffer, rl->cord.pos) - rl->cord.pos,
	&rl->cord);
}

void	rl_k_shift_right(t_readline *rl)
{
	short	start;
	short	end;
	short	pos;

	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	if (!(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl->cord.highlight_pos = rl->cord.pos;
	start = RL_MIN(rl->cord.pos + 1, rl->cord.highlight_pos);
	end = RL_MAX(rl->cord.pos + 1, rl->cord.highlight_pos);
	pos = rl->cord.pos;
	rl_go_left(rl->cord.pos, &rl->cord);
	rl_print_highlight(rl->line.buffer, start, end, &rl->cord);
	rl_go_left(rl->cord.pos - (pos + 1), &rl->cord);
}
