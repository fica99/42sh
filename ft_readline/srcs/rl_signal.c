/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 16:18:06 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/02 16:55:13 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_win_handler(int sign)
{
	t_rl_cord	cord;
	short		pos;

	if (sign == SIGWINCH)
	{
		cord = g_rl.cord;
		pos = cord.pos;
		g_rl.cord.pos -= (cord.x_cur - cord.x_start + ((cord.y_cur
		- cord.y_start) * cord.ws_col));
		rl_set_attr(&g_rl.canon_mode);
		rl_get_win_size(&g_rl.cord);
		rl_go_to_cord(0, g_rl.cord.y_start);
		ft_putstr(RL_CLEAR_END_SCREEN);
		ft_putstr(g_rl.prompt);
		rl_set_non_canon_mode(&g_rl.non_canon_mode);
		rl_get_cur_cord(&g_rl.cord);
		rl_set_start_cord(&g_rl.cord);
		rl_set_end_cord(&g_rl.cord);
		rl_print(g_rl.line.buffer + g_rl.cord.pos, &g_rl.cord);
		rl_go_left(g_rl.cord.pos - pos, &g_rl.cord);
	}
}
