/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:27:00 by filip             #+#    #+#             */
/*   Updated: 2019/06/13 18:53:46 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*print_move(char *c, t_buff *buffer, t_cord *cord, t_history *history)
{
	short len;

	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start)
	* cord->ws_col);
	(void)history;
	if ((!ft_strcmp(c, tigetstr("kcub1")) || !ft_strcmp(c, tigetstr("khome")))
	&& len)
		!ft_strcmp(c, tigetstr("kcub1")) ? go_left(1, cord) : go_left(len,
		cord);
	else if ((!ft_strcmp(c, tigetstr("kcuf1")) || !ft_strcmp(c,
	tigetstr("kend"))) && ((short)ft_strlen(buffer->buffer) > len))
		!ft_strcmp(c, tigetstr("kcuf1")) ? go_right(1, cord) :
		go_right(ft_strlen(buffer->buffer) - len, cord);
	else if (!ft_strcmp(c, CTRL_LEFT) || !ft_strcmp(c, CTRL_RIGHT))
		!ft_strcmp(c, CTRL_RIGHT) ? next_word(buffer->buffer + len, cord) :
		prev_word(buffer->buffer, len, cord);
	else if (!(ft_strcmp(c, CTRL_UP)) && len - cord->ws_col >= 0)
		go_left(cord->ws_col, cord);
	else if (!ft_strcmp(c, CTRL_DOWN) && (len + cord->ws_col <=
	(short)ft_strlen(buffer->buffer)))
		go_right(cord->ws_col, cord);
	else
		return (NULL);
	return (SOMETHING);
}

char	*print_symbols(char *c, t_buff *buffer, t_cord *cord,
t_history *history)
{
	if (!ft_strcmp(c, tigetstr("kLFT")) || !ft_strcmp(c, tigetstr("kRIT")) ||
		*c == CTRL_V || *c == CTRL_B || *c == CTRL_N)	
		cut_copy_paste(c, buffer, cord);
	//else if (*c == TAB)
		//autocom();
	else if (!ft_strcmp(c, tigetstr("kcuu1")) || !ft_strcmp(c, tigetstr("kcud1"))
	|| *c == CTRL_R || (g_flags & HISTORY_SEARCH))
		go_history(c, history, cord, buffer);
	else
		return (NULL);
	return (SOMETHING);
}

char	*print_read(char *c, char *buffer, t_cord *cord)
{
	short len;

	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start)
	* cord->ws_col);
	if (((*c == BCSP || *c == CTRL_H) && len) ||
	!ft_strcmp(c, tigetstr("kdch1")) || *c == CTRL_D)
	{
		if (*c == BCSP || *c == CTRL_H)
		{
			go_left(1, cord);
			len--;
		}
		if (!ft_strlen(buffer) && *c == CTRL_D)
		{
			g_flags |= TERM_EXIT;
			return (SOMETHING);
		}
		del_symb(buffer, len);
	}
	else if (ft_isprint(*c))
		print_symb(c, buffer, len, cord);
	else
		return (NULL);
	return (SOMETHING);
}

void	cut_copy_paste(char *c, t_buff *buffer, t_cord *cord)
{
	static short	x_cur;
	static short	y_cur;
	short			len;

	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start)
	* cord->ws_col);
	if (!x_cur && !y_cur)
	{
		x_cur = cord->x_cur;
		y_cur = cord->y_cur;
	}
	if (!ft_strcmp(c, tigetstr("kLFT")) && len)
	{
		go_left(len, cord);
		ft_putstr_highlight(buffer->buffer, len, cord);
		go_left(ft_strlen(buffer->buffer) - len, cord);
	}
	else if (!ft_strcmp(c, tigetstr("kRIT")) &&
	((short)ft_strlen(buffer->buffer) > len))
	{
		go_right(1, cord);
	}
}
