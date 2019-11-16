/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 19:00:21 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/16 23:45:03 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_enter(t_readline *rl)
{
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	rl_go_to_cord(rl->cord.x_end, rl->cord.y_end);
	ft_putstr(RL_CLEAR_END_SCREEN);
	ft_putchar('\n');
	g_rl_flags |= RL_BREAK_FLAG;
}

void	rl_k_ctrl_d(t_readline *rl)
{
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord) && rl_is_start_pos(rl->cord))
	{
		rl_go_left(rl->cord.pos, &rl->cord);
		rl_set_end_cord(&rl->cord);
		ft_putstr(RL_CLEAR_END_SCREEN);
		rl_check_str_mem(&rl->line, "exit");
		rl_print(ft_strcpy(rl->line.buffer, "exit"), &rl->cord);
	}
	else
	{
		if (rl->mode == EMACS)
		{
			if (!rl_is_end_pos(rl->cord))
				rl_del_symb(rl->line.buffer, &rl->cord);
			return ;
		}
	}
	rl_k_enter(rl);
}

void	rl_print_symb(char *c, t_readline *rl)
{
	short	pos;

	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
	{
		rl_check_str_mem(&rl->history.search, c);
		ft_strcat(rl->history.search.buffer, c);
		rl_find_history(rl, rl->history.hist_len);
	}
	else
	{
		if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
		(g_rl_flags & RL_HIGHLIGHT_FLAG))
			rl_disable_line(rl);
		pos = rl->cord.pos;
		rl_check_str_mem(&rl->line, c);
		if (!(ft_stradd(rl->line.buffer, c, pos)))
			rl_err("42sh", "malloc() error", ENOMEM);
		ft_putstr(RL_CUR_INVIS);
		rl_print(rl->line.buffer + rl->cord.pos, &rl->cord);
		rl_go_left(rl->cord.pos - pos - ft_strlen(c), &rl->cord);
		ft_putstr(RL_CUR_VIS);
	}
}

void	rl_k_del(t_readline *rl)
{
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	rl_del_symb(rl->line.buffer, &rl->cord);
}

void	rl_k_bcsp(t_readline *rl)
{
	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
	{
		ft_strdel_el(rl->history.search.buffer,
		ft_strlen(rl->history.search.buffer) - 1);
		rl_find_history(rl, rl->history.hist_len);
	}
	else
	{
		if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
		(g_rl_flags & RL_HIGHLIGHT_FLAG))
			rl_disable_line(rl);
		if (g_rl_flags & RL_COMMAND_MODE)
			return ;
		if (rl_is_start_pos(rl->cord))
			return ;
		rl_go_left(1, &rl->cord);
		rl_del_symb(rl->line.buffer, &rl->cord);
	}
}
