/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:25:49 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/11 16:59:37 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_up(t_readline *rl)
{
	if (g_rl_flags)
		rl_disable_line(rl);
	if (!rl->history.hist_index)
		return ;
	if (rl->history.hist_index-- == rl->history.hist_len)
		ft_strcpy(rl->save_line, rl->line);
	ft_strcpy(rl->line, rl->history.history_buff[rl->history.hist_index]);
	rl->cord.x_cur = rl->cord.x_start;
	rl->cord.y_cur = rl->cord.y_start;
	rl_set_end_cord(&rl->cord);
	rl->cord.pos = 0;
	ft_putstr(RL_CUR_INVIS);
	rl_go_to_cord(rl->cord.x_start, rl->cord.y_start);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_print(rl->line, &rl->cord);
	ft_putstr(RL_CUR_VIS);
}

void	rl_k_down(t_readline *rl)
{
	char	*history_buffer;

	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl->history.hist_index == rl->history.hist_len)
		return ;
	if (++(rl->history.hist_index) == rl->history.hist_len)
		history_buffer = rl->save_line;
	else
		history_buffer = rl->history.history_buff[rl->history.hist_index];
	ft_strcpy(rl->line, history_buffer);
	rl->cord.x_cur = rl->cord.x_start;
	rl->cord.y_cur = rl->cord.y_start;
	rl_set_end_cord(&rl->cord);
	rl->cord.pos = 0;
	ft_putstr(RL_CUR_INVIS);
	rl_go_to_cord(rl->cord.x_start, rl->cord.y_start);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_print(rl->line, &rl->cord);
	ft_putstr(RL_CUR_VIS);
}
