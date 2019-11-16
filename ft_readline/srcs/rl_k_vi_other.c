/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_vi_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 00:01:27 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/17 00:13:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_e(t_readline *rl)
{
	short	pos;

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	pos = rl->cord.pos;
	if (ft_isspace(rl->line.buffer[pos]))
		pos = rl_next_word(rl->line.buffer, pos);
	if (!ft_isalnum(rl->line.buffer[pos]))
		return ;
	while (ft_isalnum(rl->line.buffer[pos]))
		++pos;
	rl_go_right(pos - 1 - rl->cord.pos, &rl->cord);
}
