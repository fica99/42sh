/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:27:00 by filip             #+#    #+#             */
/*   Updated: 2019/07/02 23:10:17 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*print_move(char *c, char *buffer, t_cord *cord)
{
	short	len;

	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start) * cord->ws_col);
	disable_highlight(cord, buffer);
	if ((!ft_strcmp(c, tigetstr("kcub1")) || !ft_strcmp(c, tigetstr("khome")))
	&& !is_start_pos(cord))
		!ft_strcmp(c, tigetstr("kcub1")) ? go_left(1, cord) : go_left(cord->pos,
		cord);
	else if ((!ft_strcmp(c, tigetstr("kcuf1")) || !ft_strcmp(c,
	tigetstr("kend"))) && ((short)ft_strlen(buffer) > cord->pos))
		!ft_strcmp(c, tigetstr("kcuf1")) ? go_right(1, cord) :
		go_right(ft_strlen(buffer) - cord->pos, cord);
	else if (!ft_strcmp(c, CTRL_LEFT) || !ft_strcmp(c, CTRL_RIGHT))
		!ft_strcmp(c, CTRL_RIGHT) ? next_word(buffer + cord->pos, cord) :
		prev_word(buffer, cord);
	else if (!(ft_strcmp(c, CTRL_UP)) && len - cord->ws_col >= 0 &&
	!(g_flags & TERM_NL))
		go_left(cord->ws_col, cord);
	else if (!ft_strcmp(c, CTRL_DOWN) && (cord->pos + cord->ws_col <=
	(short)ft_strlen(buffer)) && !(g_flags & TERM_NL))
		go_right(cord->ws_col, cord);
	else
		return (NULL);
	return (SOMETHING);
}

char	*print_symbols(char *c, t_line *line)
{
	if (!ft_strcmp(c, tigetstr("kLFT")) || !ft_strcmp(c, tigetstr("kRIT")) ||
		*c == CTRL_V || *c == CTRL_C || *c == CTRL_X)
		cut_copy_paste(c, line);
	//else if (*c == TAB)
		//autocom();
	else if (!ft_strcmp(c, tigetstr("kcuu1")) || !ft_strcmp(c, tigetstr("kcud1"))
	|| *c == CTRL_R || (g_flags & HISTORY_SEARCH))
		go_history(c, line);
	else
		return (NULL);
	return (SOMETHING);
}

char	*print_printable(char *c, char *buffer, t_cord *cord)
{
	if (((*c == BCSP || *c == CTRL_H) && !is_start_pos(cord)) ||
	!ft_strcmp(c, tigetstr("kdch1")) || *c == CTRL_D)
	{
		if (*c == BCSP || *c == CTRL_H)
			go_left(1, cord);
		if (!ft_strlen(buffer) && *c == CTRL_D)
		{
			g_flags |= TERM_EXIT;
			return (SOMETHING);
		}
		del_symb(buffer, cord);
	}
	else if (ft_isprint(*c) || *c == '\n')
		print_symb(c, buffer, cord);
	else
		return (NULL);
	return (SOMETHING);
}
