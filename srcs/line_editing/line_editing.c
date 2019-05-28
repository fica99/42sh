/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:27:46 by filip             #+#    #+#             */
/*   Updated: 2019/05/28 23:12:52 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	go_left(short i)
{
	char	*cursor;

	g_term.x_cur -= i;
	while (g_term.x_cur < 0)
	{
		g_term.x_cur += g_term.ws_col;
		g_term.y_cur--;
	}
	cursor = tigetstr("cup");
	ft_putstr_fd(tparm(cursor, g_term.y_cur, g_term.x_cur), STDIN_FILENO);
}

void	go_right(short i)
{
	char	*cursor;

	g_term.x_cur += i;
	while (g_term.x_cur >= g_term.ws_col)
	{
		g_term.x_cur -= g_term.ws_col;
		g_term.y_cur++;
	}
	cursor = tigetstr("cup");
	ft_putstr_fd(tparm(cursor, g_term.y_cur, g_term.x_cur), STDIN_FILENO);
}

void	prev_word(char *buf, short len)
{
	short	i;

	i = len;
	while (--i >= 0)
	{
		if ((i == 0 || buf[i - 1] == ' ') &&
		(ft_isalpha(buf[i]) || ft_isdigit(buf[i])))
		{
			go_left(len - i);
			break ;
		}
	}
}

void	next_word(char *buf)
{
	short	i;
	char	flag;

	i = 0;
	flag = 0;
	while (buf[i])
	{
		if (buf[i] == ' ')
			flag = 1;
		if ((ft_isalpha(buf[i]) || ft_isdigit(buf[i])) && flag)
			break ;
		i++;
	}
	go_right(i);
}

void	del_symb(char *buf, short len)
{
	buf = ft_strdel_el(buf, len);
	ft_putstr_fd(tigetstr("sc"), STDIN_FILENO);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	ft_putstr_fd(buf + len, STDIN_FILENO);
	ft_putstr_fd(tigetstr("rc"), STDIN_FILENO);
}
