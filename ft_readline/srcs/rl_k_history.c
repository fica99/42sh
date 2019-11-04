/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:25:49 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/02 19:48:16 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_up(t_readline *rl)
{
	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_highlight(rl->line.buffer, &rl->cord);
	// if (g_line_flags & HISTORY_SEARCH)
	// 	disable_history(line);
	if (!rl->history.hist_index)
		return ;
	ft_putstr(RL_CUR_INVIS);
	rl_go_left(rl->cord.pos, &rl->cord);
	if ((rl->history.hist_index)-- == rl->history.hist_len)
	{
		rl_malloc_len(&rl->save_line, rl->line.buffer + rl->cord.pos);
		ft_strcpy(rl->save_line.buffer, rl->line.buffer + rl->cord.pos);
	}
	rl_malloc_len(&rl->line,
	rl->history.history_buff[rl->history.hist_index]);
	ft_strcpy(rl->line.buffer + rl->cord.pos,
	rl->history.history_buff[rl->history.hist_index]);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_print(rl->line.buffer + rl->cord.pos, &rl->cord);
	ft_putstr(RL_CUR_VIS);
}

void	rl_k_down(t_readline *rl)
{
	char	*history_buffer;

	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_highlight(rl->line.buffer, &rl->cord);
	// if (g_line_flags & HISTORY_SEARCH)
	// 	disable_history(line);
	if (rl->history.hist_index == rl->history.hist_len)
		return ;
	ft_putstr(RL_CUR_INVIS);
	rl_go_left(rl->cord.pos, &rl->cord);
	if (++(rl->history.hist_index) == rl->history.hist_len)
		history_buffer = rl->save_line.buffer;
	else
		history_buffer =rl->history.history_buff[rl->history.hist_index];
	rl_malloc_len(&rl->line, history_buffer);
	ft_strcpy(rl->line.buffer + rl->cord.pos, history_buffer);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_print(rl->line.buffer + rl->cord.pos, &rl->cord);
	ft_putstr(RL_CUR_VIS);
}
