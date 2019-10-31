/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_spec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 19:00:21 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/02 16:53:22 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_enter(t_readline *rl)
{
	t_rl_cord	cord;

	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_highlight(rl->line.buffer, &rl->cord);
	// if (g_line_flags & HISTORY_SEARCH)
	// 	disable_history(line);
	cord = rl->cord;
	rl_go_right(cord.x_end - cord.x_cur + ((cord.y_end - cord.y_cur) *
	cord.ws_col), &rl->cord);
	ft_putstr(RL_CLEAR_END_SCREEN);
	ft_putchar('\n');
	rl_is_end_window(&rl->cord);
	rl_check_quotes(rl->line.buffer, rl);
	g_rl_flags |= RL_BREAK_FLAG;
}

void	rl_k_del(t_readline *rl)
{
	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_highlight(rl->line.buffer, &rl->cord);
	// if (g_line_flags & HISTORY_SEARCH)
	// 	disable_history(line);
	if (rl_is_end_pos(rl->cord))
		return ;
	rl_del_symb(rl->line.buffer, &rl->cord);
}

void	rl_k_bcsp(t_readline *rl)
{
	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_highlight(rl->line.buffer, &rl->cord);
	if (rl_is_start_pos(rl->cord))
		return ;
	rl_go_left(1, &rl->cord);
	rl_del_symb(rl->line.buffer, &rl->cord);
}

void	rl_k_ctrl_d(t_readline *rl)
{
	t_rl_cord	cord;

	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_highlight(rl->line.buffer, &rl->cord);
	// if (g_line_flags & HISTORY_SEARCH)
	// 	disable_history(line);
	if (rl_is_end_pos(rl->cord))
	{
		if (*rl->line.buffer == '\0')
			rl_print(ft_strcpy(rl->line.buffer, "exit"), &rl->cord);
		cord = rl->cord;
		rl_go_right(cord.x_end - cord.x_cur + ((cord.y_end - cord.y_cur) *
		cord.ws_col), &rl->cord);
		ft_putstr(RL_CLEAR_END_SCREEN);
		ft_putchar('\n');
		rl_is_end_window(&rl->cord);
		g_rl_flags |= RL_BREAK_FLAG;
	}
	else
		rl_k_del(rl);
}
