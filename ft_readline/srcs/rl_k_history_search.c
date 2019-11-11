/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_history_search.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 20:31:16 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/11 18:05:00 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_ctrl_r(t_readline *rl)
{
	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_line(rl);
	if (!(g_rl_flags & RL_HISTORY_SEARCH_FLAG))
	{
		ft_strcpy(rl->save_line, rl->line);
		rl_print_hist_search(rl);
	}
	else
		rl_find_history(rl, NULL);
}

void	rl_k_ctrl_j(t_readline *rl)
{
	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
		rl_disable_line(rl);
	else
	{
		if (g_rl_flags & RL_HIGHLIGHT_FLAG)
			rl_disable_line(rl);
		rl_go_to_cord(rl->cord.x_end, rl->cord.y_end);
		ft_putstr(RL_CLEAR_END_SCREEN);
		ft_putchar('\n');
		g_rl_flags |= RL_BREAK_FLAG;
	}
}

void	rl_k_esc(t_readline *rl)
{
	if (g_rl_flags)
		rl_disable_line(rl);
}

void	rl_k_ctrl_g(t_readline *rl)
{
	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
	{
		ft_strcpy(rl->line, rl->save_line);
		rl->history.hist_index = rl->history.hist_len;
		rl_disable_line(rl);
	}
}

void	rl_find_history(t_readline *rl, char *c)
{
	short	i;
	short	index;
	char	copy[MAX_LINE_SIZE];

	*copy = '\0';
	ft_strcat(ft_strcat(copy, rl->hist_search), c);
	i = rl->history.hist_index;
	while (--i >= 0)
	{
		if (ft_strstr(rl->history.history_buff[i], copy))
		{
			rl_go_left(rl->cord.pos, &rl->cord);
			rl_set_end_cord(&rl->cord);
			ft_putstr(RL_CLEAR_END_SCREEN);
			ft_strcpy(rl->line + rl->cord.pos, rl->history.history_buff[i]);
			index = ft_strstr(rl->line, copy) - rl->line;
			rl->history.hist_index = i;
			rl_print(rl->line + rl->cord.pos, &rl->cord);
			ft_strcpy(rl->hist_search, copy);
			rl_print_hist_search(rl);
			rl_go_left(rl->cord.pos - index, &rl->cord);
			break ;
		}
	}
}
