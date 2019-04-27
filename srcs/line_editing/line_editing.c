/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:27:46 by filip             #+#    #+#             */
/*   Updated: 2019/04/28 00:11:58 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term.h"

void	go_left(short i)
{
	g_term.x_cur -= i;
	while (g_term.x_cur <= 0)
	{
		g_term.x_cur += g_term.ws_col;
		g_term.y_cur--;
	}
	ft_putstr_fd("\033[", STDIN_FILENO);
	ft_putnbr_fd(g_term.y_cur, STDIN_FILENO);
	ft_putchar_fd(';', STDIN_FILENO);
	ft_putnbr_fd(g_term.x_cur, STDIN_FILENO);
	ft_putchar_fd('H', STDIN_FILENO);
}

void	go_right(short i)
{
	g_term.x_cur += i;
	while (g_term.x_cur > g_term.ws_col)
	{
		g_term.x_cur -= g_term.ws_col;
		g_term.y_cur++;
	}
	ft_putstr_fd("\033[", STDIN_FILENO);
	ft_putnbr_fd(g_term.y_cur, STDIN_FILENO);
	ft_putchar_fd(';', STDIN_FILENO);
	ft_putnbr_fd(g_term.x_cur, STDIN_FILENO);
	ft_putchar_fd('H', STDIN_FILENO);
}

void	prev_word(char *buf, short len)
{
	short	i;

	i = len;
	while (--i >= 0)
	{
		if ((i == 0 || buf[i - 1] == ' ')  &&
		(ft_isalpha(buf[i]) || ft_isdigit(buf[i])))
		{
			go_left(len - i);
			break;
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
			break;
		i++;
	}
	go_right(i);
}

void			del_symb(char *buf, short len)
{
	buf = ft_strdel_el(buf, len);
	SAVE_CUR(STDIN_FILENO);
	CLEAN_SCREEN(STDIN_FILENO);
	ft_putstr_fd(buf + len, STDIN_FILENO);
	RESTORE_CUR(STDIN_FILENO);
}
