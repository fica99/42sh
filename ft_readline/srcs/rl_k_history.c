/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:25:49 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/10 19:19:34 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_up(t_readline *rl)
{
	short	len;

	if (g_rl_flags)
		rl_disable_line(rl);
	if (!rl->history.hist_index)
		return ;
	rl_go_left(rl->cord.pos, &rl->cord);
	if (rl->history.hist_index-- == rl->history.hist_len)
		ft_strcpy(rl->save_line, rl->line + rl->cord.pos);
	ft_strcpy(rl->line + rl->cord.pos,
	rl->history.history_buff[rl->history.hist_index]);
	rl_disable_line(rl);
	len = rl->cord.x_end - rl->cord.x_cur + ((rl->cord.y_end -
	rl->cord.y_cur) * rl->cord.ws_col);
	rl_go_right(len, &rl->cord);
}

void	rl_k_down(t_readline *rl)
{
	char	*history_buffer;
	short	len;

	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl->history.hist_index == rl->history.hist_len)
		return ;
	rl_go_left(rl->cord.pos, &rl->cord);
	if (++(rl->history.hist_index) == rl->history.hist_len)
		history_buffer = rl->save_line;
	else
		history_buffer = rl->history.history_buff[rl->history.hist_index];
	ft_strcpy(rl->line + rl->cord.pos, history_buffer);
	rl_disable_line(rl);
	len = rl->cord.x_end - rl->cord.x_cur + ((rl->cord.y_end -
	rl->cord.y_cur) * rl->cord.ws_col);
	rl_go_right(len, &rl->cord);
}

void	rl_k_ctrl_r(t_readline *rl)
{
	short	len;

	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_line(rl);
	len = rl->cord.x_end - rl->cord.x_cur + ((rl->cord.y_end -
	rl->cord.y_cur) * rl->cord.ws_col);
	rl_go_right(len, &rl->cord);
	ft_putstr(RL_CLEAR_END_SCREEN);
	ft_putchar('\n');
	rl_is_end_window(&rl->cord);
	ft_putstr("incremental history search: ");
	ft_putstr(rl->hist_search);
	rl_go_to_cord(rl->cord.x_cur, rl->cord.y_cur);
	g_rl_flags |= RL_HISTORY_SEARCH_FLAG;
}

void	rl_find_history(t_readline *rl, char *c)
{
	short	i;
	short	index;
	char	copy[MAX_LINE_SIZE];

	*copy = '\0';
	ft_strcat(ft_strcat(copy, rl->hist_search), c);
	rl_go_left(rl->cord.pos, &rl->cord);
	rl_set_end_cord(&rl->cord);
	ft_putstr(RL_CLEAR_END_SCREEN);
	i = rl->history.hist_len;
	index = 0;
	while (--i >= 0 && *copy)
	{
		if (ft_strstr(rl->history.history_buff[i], (char*)copy))
		{
			ft_strcpy(rl->line + rl->cord.pos, rl->history.history_buff[i]);
			ft_strcpy(rl->hist_search, (char*)copy);
			index = ft_strstr(rl->line +
			rl->cord.pos, (char*)copy) - (rl->line + rl->cord.pos);
			break ;
		}
	}
	rl_print(rl->line + rl->cord.pos, &rl->cord);
	rl_k_ctrl_r(rl);
	rl_go_left(rl->cord.pos - index, &rl->cord);
}
