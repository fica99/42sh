/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_vi5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:51:04 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/18 21:24:12 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_p_upper(t_readline *rl)
{
	short	pos;

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (*rl->copy_buff.buffer)
	{
		pos = rl->cord.pos;
		rl_check_str_mem(&rl->line, rl->copy_buff.buffer);
		if (!(ft_stradd(rl->line.buffer, rl->copy_buff.buffer, pos)))
			rl_err("42sh", "malloc() error", ENOMEM);
		ft_putstr(RL_CUR_INVIS);
		rl_print(rl->line.buffer + rl->cord.pos, &rl->cord);
		rl_go_left(rl->cord.pos - (pos +
		ft_strlen(rl->copy_buff.buffer)), &rl->cord);
		ft_putstr(RL_CUR_VIS);
	}
}

void	rl_k_y_upper(t_readline *rl)
{
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	rl_check_str_mem(&rl->copy_buff, rl->line.buffer);
	ft_strcpy(rl->copy_buff.buffer, rl->line.buffer);
}

void	rl_k_d_upper(t_readline *rl)
{
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	rl_check_str_mem(&rl->copy_buff, rl->line.buffer + rl->cord.pos);
	ft_strcpy(rl->copy_buff.buffer, rl->line.buffer + rl->cord.pos);
	ft_strclr(rl->line.buffer + rl->cord.pos);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_set_end_cord(&rl->cord);
}
