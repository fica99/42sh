/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:25:49 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/08 18:41:40 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_up(t_readline *rl)
{
	if (g_rl_flags)
		rl_disable_line(rl);
	if (!rl->history.hist_index)
		return ;
	rl_k_home(rl);
	if (rl->history.hist_index == rl->history.hist_len)
	{
		rl_malloc_len(&rl->save_line, rl->line.buffer + rl->cord.pos);
		ft_strcpy(rl->save_line.buffer, rl->line.buffer + rl->cord.pos);
	}
	rl_malloc_len(&rl->line,
	rl->history.history_buff[--rl->history.hist_index]);
	ft_strcpy(rl->line.buffer + rl->cord.pos,
	rl->history.history_buff[rl->history.hist_index]);
	rl_disable_line(rl);
	rl_k_end(rl);
}

void	rl_k_down(t_readline *rl)
{
	char	*history_buffer;

	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl->history.hist_index == rl->history.hist_len)
		return ;
	rl_k_home(rl);
	if (++(rl->history.hist_index) == rl->history.hist_len)
		history_buffer = rl->save_line.buffer;
	else
		history_buffer =rl->history.history_buff[rl->history.hist_index];
	rl_malloc_len(&rl->line, history_buffer);
	ft_strcpy(rl->line.buffer + rl->cord.pos, history_buffer);
	rl_disable_line(rl);
	rl_k_end(rl);
}

void	rl_k_ctrl_r(t_readline *rl)
{
	if (g_rl_flags)
		rl_disable_line(rl);
	if (!rl->history.hist_len)
		return ;
	if (!(g_rl_flags & RL_HISTORY_SEARCH_FLAG))
	{
		rl_malloc_len(&rl->save_line, rl->line.buffer + rl->cord.pos);
		ft_strcpy(rl->save_line.buffer, rl->line.buffer + rl->cord.pos);
	}
	rl_k_home(rl);
	rl_go_to_cord(0, rl->cord.y_start);
	ft_putstr(RL_CLEAR_END_SCREEN);
	ft_putstr("(reverse-i-search)`");
	ft_putstr(rl->hist_search.buffer);
	ft_putstr("\':");
	rl_find_history(rl);
	rl_start_cord_data(&rl->cord);
	rl_print(rl->line.buffer + rl->cord.pos, &rl->cord);
	g_rl_flags |= RL_HISTORY_SEARCH_FLAG;
}

void	rl_find_history(t_readline *rl)
{
	int		index;
	char	*history_buffer;

	if (!(*rl->hist_search.buffer))
		return ;
	index = rl->history.hist_index;
	while (--index >= 0)
	{
		history_buffer = rl->history.history_buff[index];
		if (ft_strstr(history_buffer, rl->hist_search.buffer))
		{
			rl->history.hist_index = index;
			rl_malloc_len(&rl->line, history_buffer);
			ft_strcpy(rl->line.buffer + rl->cord.pos, history_buffer);
		}
	}
}
