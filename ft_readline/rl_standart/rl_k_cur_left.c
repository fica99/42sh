/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_cur_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:13:53 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/31 18:34:41 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_left(t_readline *rl)
{
	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_highlight(rl->line.buffer, &rl->cord);
	// if (g_line_flags & HISTORY_SEARCH)
	// 	disable_history(line);
	 if (rl_is_start_pos(rl->cord))
		return ;
	rl_go_left(1, &rl->cord);
}

void	rl_k_home(t_readline *rl)
{
	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_highlight(rl->line.buffer, &rl->cord);
	// if (g_line_flags & HISTORY_SEARCH)
	// 	disable_history(line);
	if (rl_is_start_pos(rl->cord))
		return ;
	rl_go_left(rl->cord.pos, &rl->cord);
}

void	rl_k_ctrl_up(t_readline *rl)
{
	short	len;
	t_rl_cord	cord;

	cord = rl->cord;
	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_highlight(rl->line.buffer, &rl->cord);
	// if (g_line_flags & HISTORY_SEARCH)
	// 	disable_history(line);
	len = cord.x_cur - cord.x_start + ((cord.y_cur - cord.y_start) *
	cord.ws_col);
	if (len - cord.ws_col < 0)
		return ;
	rl_go_left(rl->cord.ws_col, &rl->cord);
}

void	rl_k_ctrl_left(t_readline *rl)
{
	short	i;
	char	*buf;

	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_highlight(rl->line.buffer, &rl->cord);
	// if (g_line_flags & HISTORY_SEARCH)
	// 	disable_history(line);
	if (rl_is_start_pos(rl->cord))
		return ;
	i = rl->cord.pos;
	buf = rl->line.buffer;
	while (--i > 0)
	{
		if (ft_isspace(buf[i - 1]) && ft_isalnum(buf[i]))
			break ;
	}
	rl_go_left(rl->cord.pos- i, &rl->cord);
}
