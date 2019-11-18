/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_vi2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 00:01:27 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/18 15:06:43 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_e(t_readline *rl)
{
	short	pos;

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	pos = rl->cord.pos;
	if (ft_isspace(rl->line.buffer[pos]))
		pos = rl_next_word(rl->line.buffer, pos);
	if (!ft_isalnum(rl->line.buffer[pos]))
		return ;
	while (ft_isalnum(rl->line.buffer[pos]))
		++pos;
	rl_go_right(pos - 1 - rl->cord.pos, &rl->cord);
}

void	rl_k_carat(t_readline *rl)
{
	short	pos;

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	pos = 0;
	while (ft_isspace(rl->line.buffer[pos]))
		++pos;
	if (rl->line.buffer[pos] == '\0')
		rl_k_end(rl);
	else
		rl_go_left(rl->cord.pos - pos, &rl->cord);
}

void	rl_k_s_upper(t_readline *rl)
{
	g_rl_flags |= RL_VI_INPUT_MODE;
	g_rl_flags &= ~RL_VI_COMMAND_MODE;
	ft_strclr(rl->line.buffer);
	rl_disable_line(rl);
}

void	rl_k_s_lower(t_readline *rl)
{
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	g_rl_flags |= RL_VI_INPUT_MODE;
	g_rl_flags &= ~RL_VI_COMMAND_MODE;
	if (rl_is_end_pos(rl->cord))
		return ;
	rl_del_symb(rl->line.buffer, &rl->cord);
}

void	rl_k_x_lower(t_readline *rl)
{
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (rl_is_start_pos(rl->cord))
		return ;
	rl_go_left(1, &rl->cord);
	rl_del_symb(rl->line.buffer, &rl->cord);
}
