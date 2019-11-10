/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_cur_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:08:14 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/10 18:45:29 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_right(t_readline *rl)
{
	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	rl_go_right(1, &rl->cord);
}

void	rl_k_end(t_readline *rl)
{
	short		len;
	t_rl_cord	cord;

	if (g_rl_flags)
		rl_disable_line(rl);
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
	if (g_rl_flags)
		rl_disable_line(rl);
	len = cord.x_end - cord.x_cur + ((cord.y_end - cord.y_cur) *
	cord.ws_col);
	if (len - cord.ws_col < 0)
		return ;
	rl_go_right(rl->cord.ws_col, &rl->cord);
}

void	rl_k_ctrl_right(t_readline *rl)
{
	short	i;

	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	i = rl->cord.pos - 1;
	while (rl->line[++i])
	{
		if (ft_isspace(rl->line[i]) && ft_isalnum(rl->line[i + 1]))
		{
			++i;
			break ;
		}
	}
	rl_go_right(i - rl->cord.pos, &rl->cord);
}
