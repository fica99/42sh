/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:47:16 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/02 19:38:24 by aashara-         ###   ########.fr       */
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

void	rl_disable_highlight(char *buffer, t_rl_cord *cord)
{
	short	pos;

	g_rl_flags &= ~RL_HIGHLIGHT_FLAG;
	pos = cord->pos;
	ft_putstr(RL_CUR_INVIS);
	rl_go_left(cord->pos, cord);
	rl_print(buffer + cord->pos, cord);
	rl_go_left(cord->pos - pos, cord);
	ft_putstr(RL_CUR_VIS);
	cord->highlight_pos = 0;
}
