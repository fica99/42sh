/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 19:00:21 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/11 17:46:49 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_enter(t_readline *rl)
{
	if (g_rl_flags)
		rl_disable_line(rl);
	rl_go_to_cord(rl->cord.x_end, rl->cord.y_end);
	ft_putstr(RL_CLEAR_END_SCREEN);
	ft_putchar('\n');
	g_rl_flags |= RL_BREAK_FLAG;
}

void	rl_k_ctrl_d(t_readline *rl)
{
	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
	{
		if (*rl->line == '\0')
			rl_print(ft_strcpy(rl->line, "exit"), &rl->cord);
		rl_go_to_cord(rl->cord.x_end, rl->cord.y_end);
		ft_putstr(RL_CLEAR_END_SCREEN);
		ft_putchar('\n');
		g_rl_flags |= RL_BREAK_FLAG;
	}
	else
		rl_k_del(rl);
}

void	rl_print_symb(char *c, t_readline *rl)
{
	short	pos;

	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
	{
		rl->history.hist_index = rl->history.hist_len;
		rl_find_history(rl, c);
	}
	else
	{
		if (g_rl_flags & RL_HIGHLIGHT_FLAG)
			rl_disable_line(rl);
		pos = rl->cord.pos;
		ft_stradd(rl->line, c, pos);
		ft_putstr(RL_CUR_INVIS);
		rl_print(rl->line + rl->cord.pos, &rl->cord);
		rl_go_left(rl->cord.pos - pos - ft_strlen(c), &rl->cord);
		ft_putstr(RL_CUR_VIS);
	}
}

void	rl_k_del(t_readline *rl)
{
	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	rl_del_symb(rl->line, &rl->cord);
}

void	rl_k_bcsp(t_readline *rl)
{
	short	len;

	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
	{
		rl->history.hist_index = rl->history.hist_len;
		if ((len = ft_strlen(rl->hist_search)))
			ft_strdel_el(rl->hist_search, len - 1);
		rl_find_history(rl, NULL);
	}
	else
	{
		if (g_rl_flags & RL_HIGHLIGHT_FLAG)
			rl_disable_line(rl);
		if (rl_is_start_pos(rl->cord))
			return ;
		rl_go_left(1, &rl->cord);
		rl_del_symb(rl->line, &rl->cord);
	}
}
