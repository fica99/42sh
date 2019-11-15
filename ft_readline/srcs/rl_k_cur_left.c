/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_cur_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:13:53 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/16 00:27:06 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_left(t_readline *rl)
{
	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl_is_start_pos(rl->cord))
		return ;
	rl_go_left(1, &rl->cord);
}

void	rl_k_home(t_readline *rl)
{
	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl_is_start_pos(rl->cord))
		return ;
	rl_go_to_cord(rl->cord.x_start, rl->cord.y_start);
	rl->cord.x_cur = rl->cord.x_start;
	rl->cord.y_cur = rl->cord.y_start;
	rl->cord.pos = 0;
}

void	rl_k_ctrl_up(t_readline *rl)
{
	short		len;
	t_rl_cord	cord;

	cord = rl->cord;
	if (g_rl_flags)
		rl_disable_line(rl);
	len = cord.x_cur - cord.x_start + ((cord.y_cur - cord.y_start) *
	cord.ws_col);
	if (len - cord.ws_col < 0)
		return ;
	rl_go_left(rl->cord.ws_col, &rl->cord);
}

void	rl_k_ctrl_left(t_readline *rl)
{
	short	pos;
	char	*buff;

	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl_is_start_pos(rl->cord))
		return ;
	pos = rl->cord.pos;
	buff = rl->line.buffer;
	while (--pos > 0)
		if (ft_isspace(buff[pos - 1]) && ft_isalnum(buff[pos]))
			break ;
	rl_go_left(rl->cord.pos - pos, &rl->cord);
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
	start = rl->cord.pos - 1;
	end = rl->cord.highlight_pos;
	if (end < start)
	{
		start = end;
		end = rl->cord.pos - 1;
	}
	pos = rl->cord.pos;
	rl_go_left(rl->cord.pos, &rl->cord);
	rl_print_highlight(rl->line.buffer, start, end, &rl->cord);
	rl_go_left(rl->cord.pos - (pos - 1), &rl->cord);
}
