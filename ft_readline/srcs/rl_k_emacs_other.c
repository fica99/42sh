/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_emacs_other.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:26:24 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/16 18:59:33 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_ctrl_t(t_readline *rl)
{
	char	symb;
	short	pos;

	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl_is_start_pos(rl->cord))
		return ;
	pos = rl->cord.pos;
	if (rl_is_end_pos(rl->cord))
	{
		if (--pos <= 0)
			return ;
	}
	symb = rl->line.buffer[pos];
	rl->line.buffer[pos] = rl->line.buffer[pos - 1];
	rl->line.buffer[pos - 1] = symb;
	rl_disable_line(rl);
	rl_go_right(1, &rl->cord);
}
