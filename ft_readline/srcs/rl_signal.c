/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 16:18:06 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/10 19:19:14 by aashara-         ###   ########.fr       */
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
		rl_get_win_size(&g_rl.cord);
		ft_putstr(RL_CLEAR_END_SCREEN);
		ft_putchar('\n');
		rl_write_prompt(g_rl.prompt, g_rl.env, g_rl.history);
		rl_start_cord_data(&g_rl.cord);
		rl_print(g_rl.line + g_rl.cord.pos, &g_rl.cord);
		rl_go_left(g_rl.cord.pos - pos, &g_rl.cord);
	}
}
