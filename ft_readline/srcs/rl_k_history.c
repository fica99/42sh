/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:25:49 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/08 23:26:26 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_up(t_readline *rl)
{
	if (g_rl_flags)
		rl_disable_line(rl);
	if (!rl->history.hist_index)
		return ;
	rl_k_home(rl);
	if (rl->history.hist_index == rl->history.hist_len)
	{
		rl_malloc_len(&rl->save_line, rl->line.buffer + rl->cord.pos);
		ft_strcpy(rl->save_line.buffer, rl->line.buffer + rl->cord.pos);
	}
	rl_malloc_len(&rl->line,
	rl->history.history_buff[--rl->history.hist_index]);
	ft_strcpy(rl->line.buffer + rl->cord.pos,
	rl->history.history_buff[rl->history.hist_index]);
	rl_disable_line(rl);
	rl_k_end(rl);
}

void	rl_k_down(t_readline *rl)
{
	char	*history_buffer;

	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl->history.hist_index == rl->history.hist_len)
		return ;
	rl_k_home(rl);
	if (++(rl->history.hist_index) == rl->history.hist_len)
		history_buffer = rl->save_line.buffer;
	else
		history_buffer =rl->history.history_buff[rl->history.hist_index];
	rl_malloc_len(&rl->line, history_buffer);
	ft_strcpy(rl->line.buffer + rl->cord.pos, history_buffer);
	rl_disable_line(rl);
	rl_k_end(rl);
}

void	rl_k_ctrl_r(t_readline *rl)
{
	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_line(rl);
	rl_go_right(ft_strlen(rl->line.buffer + rl->cord.pos), &rl->cord);
	ft_putstr(RL_CLEAR_END_SCREEN);
	ft_putchar('\n');
	if (rl->cord.y_end >= rl->cord.ws_row - 1)
	{
		--rl->cord.y_cur;
		--rl->cord.y_start;
		--rl->cord.y_end;
	}
	ft_putstr("incremental history search: ");
	ft_putstr(rl->hist_search.buffer);
	rl_go_to_cord(rl->cord.x_cur, rl->cord.y_cur);
	g_rl_flags |= RL_HISTORY_SEARCH_FLAG;
}

void	rl_find_history(t_readline *rl, char *c)
{
	short	i;
	char	*history;

	rl_malloc_len(&rl->save_line, rl->hist_search.buffer);
	ft_strcat(rl->save_line.buffer, rl->hist_search.buffer);
	ft_strcat(rl->save_line.buffer, c);
	rl_go_left(rl->cord.pos, &rl->cord);
	rl_set_end_cord(&rl->cord);
	ft_putstr(RL_CLEAR_END_SCREEN);
	i = rl->history.hist_len;
	while (--i >= 0 && *rl->save_line.buffer)
	{
		history = rl->history.history_buff[i];
		if (ft_strstr(history, rl->save_line.buffer))
		{
			rl_malloc_len(&rl->line, history);
			ft_strcpy(rl->line.buffer + rl->cord.pos, history);
			ft_strcpy(rl->hist_search.buffer, rl->save_line.buffer);
			break ;
		}
	}
	rl_print(rl->line.buffer + rl->cord.pos, &rl->cord);
	ft_strclr(rl->save_line.buffer);
	rl_k_ctrl_r(rl);
}
