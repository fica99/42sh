/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_cur_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:13:53 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/14 20:13:26 by aashara-         ###   ########.fr       */
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
	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl_is_start_pos(rl->cord))
		return ;
	rl_go_left(rl->cord.pos - rl_prev_word(rl->line.buffer,
	rl->cord.pos), &rl->cord);
}
