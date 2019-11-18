/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_vi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:51:24 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/18 21:57:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_i_lower(t_readline *rl)
{
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	g_rl_flags |= RL_VI_INPUT_MODE;
	g_rl_flags &= ~RL_VI_COMMAND_MODE;
}

void	rl_k_i_upper(t_readline *rl)
{
	g_rl_flags |= RL_VI_INPUT_MODE;
	g_rl_flags &= ~RL_VI_COMMAND_MODE;
	rl_k_home(rl);
}

void	rl_k_a_lower(t_readline *rl)
{
	g_rl_flags |= RL_VI_INPUT_MODE;
	g_rl_flags &= ~RL_VI_COMMAND_MODE;
	rl_k_right(rl);
}

void	rl_k_a_upper(t_readline *rl)
{
	g_rl_flags |= RL_VI_INPUT_MODE;
	g_rl_flags &= ~RL_VI_COMMAND_MODE;
	rl_k_end(rl);
}

void	rl_k_sharp(t_readline *rl)
{
	if (!(ft_stradd(rl->line.buffer, RL_K_SHARP, 0)))
		rl_err("42sh", "malloc() error", ENOMEM);
	rl_disable_line(rl);
	rl_k_enter(rl);
}
