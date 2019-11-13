/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_highlight.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:35:44 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/13 19:53:45 by aashara-         ###   ########.fr       */
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
	rl_print_highlight(rl->line, start, end, &rl->cord);
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
	rl_print_highlight(rl->line, start, end, &rl->cord);
	rl_go_left(rl->cord.pos - (pos + 1), &rl->cord);
}

void	rl_k_ctrl_c(t_readline *rl)
{
	short	start;
	short	end;

	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
		rl_disable_line(rl);
	if (!(g_rl_flags & RL_HIGHLIGHT_FLAG))
	{
		*rl->line = '\0';
		rl_go_to_cord(rl->cord.x_end, rl->cord.y_end);
		ft_putstr(RL_CLEAR_END_SCREEN);
		ft_putchar('\n');
		g_rl_flags |= RL_BREAK_FLAG;
	}
	else
	{
		start = rl->cord.pos;
		end = rl->cord.highlight_pos;
		if (end < start)
		{
			start = end;
			end = rl->cord.pos;
		}
		ft_strncpy(rl->copy_buff, rl->line + start, end - start);
	}
}

void	rl_k_ctrl_x(t_readline *rl)
{
	short	start;
	short	end;
	short	j;

	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
		rl_disable_line(rl);
	if (!(g_rl_flags & RL_HIGHLIGHT_FLAG))
		return ;
	start = rl->cord.pos;
	end = rl->cord.highlight_pos;
	if (end < start)
	{
		start = end;
		end = rl->cord.pos;
	}
	ft_strncpy(rl->copy_buff, rl->line + start, end - start);
	j = start;
	while (++j <= end)
		ft_strdel_el(rl->line, start);
	rl_disable_line(rl);
}

void	rl_k_ctrl_v(t_readline *rl)
{
	short	pos;

	if (g_rl_flags)
		rl_disable_line(rl);
	if (*rl->copy_buff)
	{
		pos = rl->cord.pos;
		ft_stradd(rl->line, rl->copy_buff, pos);
		ft_putstr(RL_CUR_INVIS);
		rl_print(rl->line + rl->cord.pos, &rl->cord);
		rl_go_left(rl->cord.pos - pos - ft_strlen(rl->copy_buff), &rl->cord);
		ft_putstr(RL_CUR_VIS);
	}
}
