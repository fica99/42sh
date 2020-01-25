/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_cut_copy_paste.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 23:13:41 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/22 16:47:54 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_ctrl_c(t_readline *rl)
{
	short	s;
	short	e;

	if (!(g_rl_flags & RL_HIGHLIGHT_FLAG))
	{
		ft_strclr(rl->line.buffer);
		*rl->line.buffer = RL_K_CTRL_C;
		rl_k_enter(rl);
	}
	else
	{
		s = ft_min(rl->cord.pos, rl->cord.highlight_pos);
		e = ft_max(rl->cord.pos, rl->cord.highlight_pos);
		rl_check_str_mem(&rl->copy_buff, rl->line.buffer + s);
		ft_strncpy(rl->copy_buff.buffer, rl->line.buffer + s, e - s);
	}
}

void	rl_k_ctrl_x(t_readline *rl)
{
	short	s;
	short	e;
	short	j;

	if (!(g_rl_flags & RL_HIGHLIGHT_FLAG))
	{
		if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
			rl_disable_line(rl);
		return ;
	}
	s = ft_min(rl->cord.pos, rl->cord.highlight_pos);
	e = ft_max(rl->cord.pos, rl->cord.highlight_pos);
	rl_check_str_mem(&rl->copy_buff, rl->line.buffer + s);
	ft_strncpy(rl->copy_buff.buffer, rl->line.buffer + s, e - s);
	j = s;
	while (++j <= e)
		ft_strdel_el(rl->line.buffer, s);
	rl_disable_line(rl);
}

void	rl_k_ctrl_v(t_readline *rl)
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
		ft_putstr(tigetstr("civis"));
		rl_print(rl->line.buffer + rl->cord.pos, &rl->cord);
		rl_go_left(rl->cord.pos - (pos +
		ft_strlen(rl->copy_buff.buffer)), &rl->cord);
		ft_putstr(tigetstr("cvvis"));
	}
}

void	rl_k_ctrl_k(t_readline *rl)
{
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	rl_check_str_mem(&rl->copy_buff, rl->line.buffer + rl->cord.pos);
	ft_strcpy(rl->copy_buff.buffer, rl->line.buffer + rl->cord.pos);
	ft_strclr(rl->line.buffer + rl->cord.pos);
	ft_putstr(tigetstr("ed"));
	rl_set_end_cord(&rl->cord);
}

void	rl_k_ctrl_u(t_readline *rl)
{
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (rl_is_start_pos(rl->cord))
		return ;
	rl_check_str_mem(&rl->copy_buff, rl->line.buffer);
	ft_strncpy(rl->copy_buff.buffer, rl->line.buffer, rl->cord.pos);
	ft_strcpy(rl->line.buffer, rl->line.buffer + rl->cord.pos);
	rl_go_left(rl->cord.pos, &rl->cord);
	rl_disable_line(rl);
}
