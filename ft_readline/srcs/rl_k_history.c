/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:25:49 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/10 20:31:37 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_up(t_readline *rl)
{
	short	len;

	if (g_rl_flags)
		rl_disable_line(rl);
	if (!rl->history.hist_index)
		return ;
	rl_go_left(rl->cord.pos, &rl->cord);
	if (rl->history.hist_index-- == rl->history.hist_len)
		ft_strcpy(rl->save_line, rl->line + rl->cord.pos);
	ft_strcpy(rl->line + rl->cord.pos,
	rl->history.history_buff[rl->history.hist_index]);
	rl_disable_line(rl);
	len = rl->cord.x_end - rl->cord.x_cur + ((rl->cord.y_end -
	rl->cord.y_cur) * rl->cord.ws_col);
	rl_go_right(len, &rl->cord);
}

void	rl_k_down(t_readline *rl)
{
	char	*history_buffer;
	short	len;

	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl->history.hist_index == rl->history.hist_len)
		return ;
	rl_go_left(rl->cord.pos, &rl->cord);
	if (++(rl->history.hist_index) == rl->history.hist_len)
		history_buffer = rl->save_line;
	else
		history_buffer = rl->history.history_buff[rl->history.hist_index];
	ft_strcpy(rl->line + rl->cord.pos, history_buffer);
	rl_disable_line(rl);
	len = rl->cord.x_end - rl->cord.x_cur + ((rl->cord.y_end -
	rl->cord.y_cur) * rl->cord.ws_col);
	rl_go_right(len, &rl->cord);
}
