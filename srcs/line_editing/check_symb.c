/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:27:00 by filip             #+#    #+#             */
/*   Updated: 2019/05/28 23:13:25 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	print_read(char *c)
{
	short len;

	len = g_term.x_cur - g_term.x_start + ((g_term.y_cur - g_term.y_start)
			* g_term.ws_col);
	if ((!(ft_strcmp(c, tigetstr("kcub1"))) ||
				!(ft_strcmp(c, tigetstr("khome")))) && len)
		!(ft_strcmp(c, tigetstr("kcub1"))) ? go_left(1) : go_left(len);
	else if ((!(ft_strcmp(c, tigetstr("kcuf1"))) ||
				!(ft_strcmp(c, tigetstr("kend")))) &&
			((short)ft_strlen(g_term.buffer) > len))
		!(ft_strcmp(c, tigetstr("kcuf1"))) ? go_right(1) :
			go_right(ft_strlen(g_term.buffer) - len);
	else if (!(ft_strcmp(c, CTRL_LEFT)) || !(ft_strcmp(c, CTRL_RIGHT)))
		!(ft_strcmp(c, CTRL_RIGHT)) ? next_word(g_term.buffer + len) :
			prev_word(g_term.buffer, len);
	else if (!(ft_strcmp(c, CTRL_UP)) && len - g_term.ws_col >= 0)
		go_left(g_term.ws_col);
	else if (!(ft_strcmp(c, CTRL_DOWN)) && (len + g_term.ws_col
				<= (short)ft_strlen(g_term.buffer)))
		go_right(g_term.ws_col);
	//else if (*c == TAB)
		//autocom();
	else
		print_read_other(c);
}

void	print_read_other(char *c)
{
	short len;

	len = g_term.x_cur - g_term.x_start + ((g_term.y_cur - g_term.y_start)
			* g_term.ws_col);
	if (!(ft_strcmp(c, tigetstr("kcuu1"))) ||
			!(ft_strcmp(c, tigetstr("kcud1"))))
		go_history(c);
	else if (((*c == BCSP || *c == CTRL_H) && len) ||
			!ft_strcmp(c, tigetstr("kdch1"))
		|| *c == CTRL_D)
	{
		if (*c == BCSP || *c == CTRL_H)
		{
			go_left(1);
			len--;
		}
		if (!ft_strlen(g_term.buffer) && *c == CTRL_D)
		{
			g_flags |= TERM_EXIT;
			return ;
		}
		del_symb(g_term.buffer, len);
	}
	else if (ft_isprint(*c))
		print_symb(c, g_term.buffer, len);
}
