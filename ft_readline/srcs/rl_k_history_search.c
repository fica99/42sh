/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_history_search.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 20:31:16 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/16 17:59:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_ctrl_r(t_readline *rl)
{
	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_line(rl);
	if (rl->history.hist_index == rl->history.hist_len)
	{
		rl_check_str_mem(&rl->history.save_line, rl->line.buffer);
		ft_strcpy(rl->history.save_line.buffer, rl->line.buffer);
	}
	if (!(g_rl_flags & RL_HISTORY_SEARCH_FLAG))
	{
		rl_check_str_mem(&rl->save_line, rl->line.buffer);
		ft_strcpy(rl->save_line.buffer, rl->line.buffer);
		rl->save_index = rl->history.hist_index;
	}
	rl_find_history(rl, rl->history.hist_index);
}

void	rl_k_ctrl_j(t_readline *rl)
{
	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
		rl_disable_line(rl);
	else
		rl_k_enter(rl);
}

void	rl_k_esc(t_readline *rl)
{
	if (g_rl_flags)
		rl_disable_line(rl);
}

void	rl_k_ctrl_g(t_readline *rl)
{
	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
	{
		rl_check_str_mem(&rl->line, rl->save_line.buffer);
		ft_strcpy(rl->line.buffer, rl->save_line.buffer);
		rl->history.hist_index = rl->save_index;
		rl_disable_line(rl);
	}
}

void	rl_find_history(t_readline *rl, short i)
{
	char	*find;
	short	index;

	find = rl->save_line.buffer;
	if (!(ft_strstr(find, rl->history.search.buffer)))
	{
		while (--i >= 0)
		{
			find = rl->history.history_buff[i];
			if ((ft_strstr(find, rl->history.search.buffer)))
			{
				rl->history.hist_index = i;
				break ;
			}
		}
	}
	rl_check_str_mem(&rl->line, find);
	ft_strcpy(rl->line.buffer, find);
	rl_print_hist_search(rl);
	index = ft_strstr(find, rl->history.search.buffer) - find;
	rl_go_left(rl->cord.pos - index, &rl->cord);
}
