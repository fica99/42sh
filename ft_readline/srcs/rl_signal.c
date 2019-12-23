/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 16:18:06 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/06 13:36:19 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_win_handler(int sign)
{
	short		pos;

	if (sign == SIGWINCH)
	{
		pos = g_rl.cord.pos;
		rl_get_win_size(&g_rl.cord);
		ft_putstr(RL_CUR_INVIS);
		ft_putstr(RL_CLEAR_END_SCREEN);
		ft_putchar('\n');
		rl_write_prompt(g_rl.prompt, g_rl.history);
		rl_start_cord_data(&g_rl.cord);
		rl_disable_line(&g_rl);
		rl_go_right(pos, &g_rl.cord);
	}
}
