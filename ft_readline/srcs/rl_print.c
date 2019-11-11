/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara <aashara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:47:16 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/11 12:03:51 by aashara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_print(char *str, t_rl_cord *cord)
{
	while (str && *str)
	{
		ft_putchar(*str);
		if (++cord->x_cur >= cord->ws_col)
		{
			ft_putchar('\n');
			cord->x_cur = 0;
			if (cord->y_cur >= cord->ws_row - 1)
				(cord->y_start)--;
			else
				(cord->y_cur)++;
		}
		str++;
		cord->pos++;
	}
	rl_set_end_cord(cord);
}

void	rl_del_symb(char *buf, t_rl_cord *cord)
{
	short	pos;

	pos = cord->pos;
	buf = ft_strdel_el(buf, pos);
	ft_putstr(RL_CUR_INVIS);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_print(buf + cord->pos, cord);
	rl_go_left(cord->pos - pos, cord);
	ft_putstr(RL_CUR_VIS);
}

void	rl_print_highlight(char *str, short start, short end, t_rl_cord cord)
{
	short	i;
	char	symb[2];

	ft_putstr(RL_CUR_INVIS);
	rl_go_left(cord.pos, &cord);
	i = -1 + cord.pos;
	if (start <= i)
		ft_putstr(HIGHLIGHT);
	symb[1] = '\0';
	while (str[++i])
	{
		if (i == start)
			ft_putstr(HIGHLIGHT);
		if (i == end)
			ft_putstr(STANDART);
		symb[0] = str[i];
		rl_print(symb, &cord);
	}
	ft_putstr(STANDART);
	ft_putstr(RL_CUR_VIS);
	g_rl_flags |= RL_HIGHLIGHT_FLAG;
}

void	rl_disable_line(t_readline *rl)
{
	short	pos;

	*rl->hist_search = '\0';
	rl->cord.highlight_pos = 0;
	g_rl_flags = RL_INIT_FLAGS;
	pos = rl->cord.pos;
	ft_putstr(RL_CUR_INVIS);
	rl_go_left(pos, &rl->cord);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_start_cord_data(&rl->cord);
	rl_print(rl->line + rl->cord.pos, &rl->cord);
	rl_go_left(rl->cord.pos - pos, &rl->cord);
	ft_putstr(RL_CUR_VIS);
}


void	rl_print_hist_search(t_readline *rl)
{
	t_rl_cord	cord;
	short		delta;

	ft_putstr(RL_CUR_INVIS);
	ft_memcpy((void*)&cord, (void*)&rl->cord, sizeof(t_rl_cord));
	rl_go_right(cord.x_end - cord.x_cur + ((cord.y_end - cord.y_cur)
	* cord.ws_col), &cord);
	ft_putstr(RL_CLEAR_END_SCREEN);
	ft_putchar('\n');
	rl_is_end_window(&cord);
	cord.x_cur = 0;
	rl_print("incremental history search: ", &cord);
	rl_print(rl->hist_search, &cord);
	delta = abs(rl->cord.y_start - cord.y_start);
	rl->cord.y_start -= delta;
	rl->cord.y_end -= delta;
	rl->cord.y_cur -= delta;
	rl_go_to_cord(rl->cord.x_cur, rl->cord.y_cur);
	ft_putstr(RL_CUR_VIS);
}
