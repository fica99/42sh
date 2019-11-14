/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_cut_copy_paste.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 23:13:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/14 23:16:42 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_ctrl_c(t_readline *rl)
{
	short	s;
	short	e;

	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
		rl_disable_line(rl);
	if (!(g_rl_flags & RL_HIGHLIGHT_FLAG))
	{
		ft_strclr(rl->line.buffer);
		rl_go_to_cord(rl->cord.x_end, rl->cord.y_end);
		ft_putstr(RL_CLEAR_END_SCREEN);
		ft_putchar('\n');
		g_rl_flags |= RL_BREAK_FLAG;
	}
	else
	{
		s = rl->cord.pos;
		e = rl->cord.highlight_pos;
		if (e < s)
		{
			s = e;
			e = rl->cord.pos;
		}
		rl_check_str_mem(&rl->copy_buff, rl->line.buffer + s);
		ft_strncpy(rl->copy_buff.buffer, rl->line.buffer + s, e - s);
	}
}

void	rl_k_ctrl_x(t_readline *rl)
{
	short	s;
	short	e;
	short	j;

	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
		rl_disable_line(rl);
	if (!(g_rl_flags & RL_HIGHLIGHT_FLAG))
		return ;
	s = rl->cord.pos;
	e = rl->cord.highlight_pos;
	if (e < s)
	{
		s = e;
		e = rl->cord.pos;
	}
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

	if (g_rl_flags)
		rl_disable_line(rl);
	if (*rl->copy_buff.buffer)
	{
		pos = rl->cord.pos;
		rl_check_str_mem(&rl->line, rl->copy_buff.buffer);
		ft_stradd(rl->line.buffer, rl->copy_buff.buffer, pos);
		ft_putstr(RL_CUR_INVIS);
		rl_print(rl->line.buffer + rl->cord.pos, &rl->cord);
		rl_go_left(rl->cord.pos - pos -
		ft_strlen(rl->copy_buff.buffer), &rl->cord);
		ft_putstr(RL_CUR_VIS);
	}
}

void	rl_k_ctrl_k(t_readline *rl)
{
	if (g_rl_flags)
		rl_disable_line(rl);
	rl_check_str_mem(&rl->copy_buff, rl->line.buffer + rl->cord.pos);
	ft_strcpy(rl->copy_buff.buffer, rl->line.buffer + rl->cord.pos);
	ft_strclr(rl->line.buffer + rl->cord.pos);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_set_end_cord(&rl->cord);
}

void	rl_k_ctrl_u(t_readline *rl)
{
	char	*copy;

	if (g_rl_flags)
		rl_disable_line(rl);
	if (!(copy = ft_strdup(rl->line.buffer + rl->cord.pos)))
		rl_err("42sh", "malloc() error", ENOMEM);
	rl->line.buffer[rl->cord.pos] = '\0';
	rl_check_str_mem(&rl->copy_buff, rl->line.buffer);
	ft_strcpy(rl->copy_buff.buffer, rl->line.buffer);
	rl_check_str_mem(&rl->line, copy);
	ft_strcpy(rl->line.buffer, copy);
	ft_strdel(&copy);
	ft_putstr(RL_CUR_INVIS);
	rl_go_left(rl->cord.pos, &rl->cord);
	rl_set_end_cord(&rl->cord);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_print(rl->line.buffer, &rl->cord);
	rl_go_left(rl->cord.pos, &rl->cord);
	ft_putstr(RL_CUR_VIS);
}
