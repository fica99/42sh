/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_highlight.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:35:44 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/14 21:06:23 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_shift_left(t_readline *rl)
{
	short		start;
	short		end;
	short		pos;

	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
		rl_disable_line(rl);
	if (rl_is_start_pos(rl->cord))
		return ;
	if (!(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl->cord.highlight_pos = rl->cord.pos;
	start = rl->cord.pos - 1;
	end = rl->cord.highlight_pos;
	if (end < start)
	{
		start = end;
		end = rl->cord.pos - 1;
	}
	pos = rl->cord.pos;
	rl_go_left(rl->cord.pos, &rl->cord);
	rl_print_highlight(rl->line.buffer, start, end, &rl->cord);
	rl_go_left(rl->cord.pos - (pos - 1), &rl->cord);
}

void	rl_k_shift_right(t_readline *rl)
{
	short	start;
	short	end;
	short	pos;

	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	if (!(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl->cord.highlight_pos = rl->cord.pos;
	start = rl->cord.highlight_pos;
	end = rl->cord.pos + 1;
	if (end < start)
	{
		end = start;
		start = rl->cord.pos + 1;
	}
	pos = rl->cord.pos;
	rl_go_left(rl->cord.pos, &rl->cord);
	rl_print_highlight(rl->line.buffer, start, end, &rl->cord);
	rl_go_left(rl->cord.pos - (pos + 1), &rl->cord);
}

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
