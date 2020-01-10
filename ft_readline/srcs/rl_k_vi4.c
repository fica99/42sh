/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_vi4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:56:50 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/08 16:53:07 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_semicolon(t_readline *rl)
{
	char	*pos;

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	if ((pos = ft_strchr(rl->line.buffer + rl->cord.pos + 1,
	rl->line.buffer[rl->cord.pos])))
		rl_go_right(pos - (rl->line.buffer + rl->cord.pos), &rl->cord);
}

void	rl_k_comma(t_readline *rl)
{
	short	new_pos;

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (rl_is_start_pos(rl->cord))
		return ;
	new_pos = rl->cord.pos - 1;
	while (new_pos >= 0)
	{
		if (rl->line.buffer[new_pos] == rl->line.buffer[rl->cord.pos])
		{
			rl_go_left(rl->cord.pos - new_pos, &rl->cord);
			break ;
		}
		--new_pos;
	}
}

void	rl_k_r_upper(t_readline *rl)
{
	char	c[RL_MAX_BUFF + 1];

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	rl_read_handler(c, STDOUT_FILENO);
	rl->line.buffer[rl->cord.pos] = *c;
	rl_disable_line(rl);
	g_rl_flags |= RL_VI_INPUT_MODE;
	g_rl_flags &= ~RL_VI_COMMAND_MODE;
}

void	rl_k_r_lower(t_readline *rl)
{
	char	c[RL_MAX_BUFF + 1];

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	rl_read_handler(c, STDOUT_FILENO);
	rl->line.buffer[rl->cord.pos] = *c;
	rl_disable_line(rl);
}

void	rl_k_p_lower(t_readline *rl)
{
	short	pos;

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (*rl->copy_buff.buffer)
	{
		pos = rl->cord.pos;
		rl_check_str_mem(&rl->line, rl->copy_buff.buffer);
		if (!(ft_stradd(rl->line.buffer, rl->copy_buff.buffer, pos + 1)))
			rl_err("42sh", "malloc() error", ENOMEM);
		ft_putstr(RL_CUR_INVIS);
		rl_print(rl->line.buffer + rl->cord.pos, &rl->cord);
		rl_go_left(rl->cord.pos - pos, &rl->cord);
		ft_putstr(RL_CUR_VIS);
	}
}
