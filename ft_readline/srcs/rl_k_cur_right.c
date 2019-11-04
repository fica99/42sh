/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_cur_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:08:14 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/04 17:25:15 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_right(t_readline *rl)
{
	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_highlight(rl->line.buffer, &rl->cord);
	if (rl_is_end_pos(rl->cord))
		return ;
	rl_go_right(1, &rl->cord);
}

void	rl_k_end(t_readline *rl)
{
	short		len;
	t_rl_cord	cord;

	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_highlight(rl->line.buffer, &rl->cord);
	if (rl_is_end_pos(rl->cord))
		return ;
	cord = rl->cord;
	len = cord.x_end - cord.x_cur + ((cord.y_end - cord.y_cur) *
	cord.ws_col);
	rl_go_right(len, &rl->cord);
}

void	rl_k_ctrl_down(t_readline *rl)
{
	short		len;
	t_rl_cord	cord;

	cord = rl->cord;
	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_highlight(rl->line.buffer, &rl->cord);
	len = cord.x_end - cord.x_cur + ((cord.y_end - cord.y_cur) *
	cord.ws_col);
	if (len - cord.ws_col < 0)
		return ;
	rl_go_right(rl->cord.ws_col, &rl->cord);
}

void	rl_k_ctrl_right(t_readline *rl)
{
	short	i;
	char	*buf;

	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_highlight(rl->line.buffer, &rl->cord);
	if (rl_is_end_pos(rl->cord))
		return ;
	i = rl->cord.pos;
	buf = rl->line.buffer;
	while (buf[i])
	{
		if (ft_isspace(buf[i]) && ft_isalnum(buf[i + 1]))
		{
			i++;
			break ;
		}
		i++;
	}
	rl_go_right(i - rl->cord.pos, &rl->cord);
}
