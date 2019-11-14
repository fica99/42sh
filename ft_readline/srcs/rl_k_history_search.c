/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_history_search.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 20:31:16 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/14 22:15:21 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_ctrl_r(t_readline *rl)
{
	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_line(rl);
	if (rl->history.hist_index == rl->history.hist_len)
	{
		rl_check_str_mem(&rl->history.save_line, rl->line.buffer);
		ft_strcpy(rl->history.save_line.buffer, rl->line.buffer);
	}
	if (!(g_rl_flags & RL_HISTORY_SEARCH_FLAG))
	{
		rl_check_str_mem(&rl->save_line, rl->line.buffer);
		ft_strcpy(rl->save_line.buffer, rl->line.buffer);
		rl->save_index = rl->history.hist_index;
		rl_find_history(rl, NULL, rl->history.hist_len, 0);
	}
	else
		rl_find_history(rl, NULL, rl->history.hist_index, 1);
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
		rl_check_str_mem(&rl->line, rl->save_line.buffer);
		ft_strcpy(rl->line.buffer, rl->save_line.buffer);
		rl->history.hist_index = rl->save_index;
		rl_disable_line(rl);
	}
}

void	rl_find_history(t_readline *rl, char *c, short i, char next)
{
	char	*find;
	char	*point;

	rl_check_str_mem(&rl->history.search, c);
	ft_strcat(rl->history.search.buffer, c);
	point = NULL;
	if (!ft_strstr(find = rl->line.buffer, rl->history.search.buffer) || next)
	{
		while (--i >= 0)
		{
			find = rl->history.history_buff[i];
			if ((point = ft_strstr(find, rl->history.search.buffer)))
			{
				rl->history.hist_index = i;
				break ;
			}
			if (i == 0)
				rl->history.search.buffer[ft_strlen(rl->history.search.buffer)
				- 1] = '\0';
		}
	}
	rl_check_str_mem(&rl->line, find);
	ft_strcpy(rl->line.buffer, find);
	rl_print_hist_search(rl);
	rl_go_left(rl->cord.pos - (point - rl->line.buffer), &rl->cord);
}
