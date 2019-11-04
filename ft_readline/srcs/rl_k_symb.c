/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_symb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 20:18:22 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/04 17:31:09 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_print_symb(char *c, t_readline *rl)
{
	short	pos;
	char	*buf;

	buf = rl->line.buffer;
	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_highlight(buf, &rl->cord);
	pos = rl->cord.pos;
	rl->line.buffer = ft_stradd(buf, c, pos);
	ft_putstr(RL_CUR_INVIS);
	rl_print(buf + rl->cord.pos, &rl->cord);
	rl_go_left(rl->cord.pos - pos, &rl->cord);
	ft_putstr(RL_CUR_VIS);
	rl_go_right(ft_strlen(c), &rl->cord);
}

void	rl_del_symb(char *buf, t_rl_cord *cord)
{
	short	pos;

	pos = cord->pos;
	if (g_rl_flags & RL_HIGHLIGHT_FLAG)
		rl_disable_highlight(buf, cord);
	buf = ft_strdel_el(buf, pos);
	ft_putstr(RL_CUR_INVIS);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_print(buf + cord->pos, cord);
	rl_go_left(cord->pos - pos, cord);
	ft_putstr(RL_CUR_VIS);
}
