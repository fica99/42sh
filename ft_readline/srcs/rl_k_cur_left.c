/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_cur_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:13:53 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/22 16:57:33 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_left(t_readline *rl)
{
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (rl_is_start_pos(rl->cord))
		return ;
	rl_go_left(1, &rl->cord);
}

void	rl_k_home(t_readline *rl)
{
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (rl_is_start_pos(rl->cord))
		return ;
	rl_go_left(rl->cord.pos, &rl->cord);
}

void	rl_k_ctrl_up(t_readline *rl)
{
	short		len;
	t_rl_cord	cord;

	cord = rl->cord;
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	len = cord.x_cur - cord.x_start + ((cord.y_cur - cord.y_start) *
	cord.ws_col);
	if (len - cord.ws_col < 0)
		return ;
	rl_go_left(rl->cord.ws_col, &rl->cord);
}

void	rl_k_ctrl_left(t_readline *rl)
{
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (rl_is_start_pos(rl->cord))
		return ;
	rl_go_left(rl->cord.pos - rl_prev_word(rl->line.buffer,
	rl->cord.pos - 1), &rl->cord);
}

void	rl_k_shift_left(t_readline *rl)
{
	short		start;
	short		end;
	short		pos;

	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
		rl_disable_line(rl);
	if (rl_is_start_pos(rl->cord))
		return ;
	if (!(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl->cord.highlight_pos = rl->cord.pos;
	start = ft_min(rl->cord.pos - 1, rl->cord.highlight_pos);
	end = ft_max(rl->cord.pos - 1, rl->cord.highlight_pos);
	pos = rl->cord.pos;
	rl_go_left(rl->cord.pos, &rl->cord);
	rl_print_highlight(rl->line.buffer, start, end, &rl->cord);
	rl_go_left(rl->cord.pos - (pos - 1), &rl->cord);
}
