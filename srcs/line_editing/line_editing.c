/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:27:46 by filip             #+#    #+#             */
/*   Updated: 2019/06/11 18:51:59 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	go_left(short i, t_cord *cord)
{
	cord->x_cur -= i;
	while (cord->x_cur < 0)
	{
		cord->x_cur += cord->ws_col;
		cord->y_cur--;
	}
	go_to_cord(cord->x_cur, cord->y_cur, STDIN_FILENO);
}

void	go_right(short i, t_cord *cord)
{
	cord->x_cur += i;
	while (cord->x_cur >= cord->ws_col)
	{
		cord->x_cur -= cord->ws_col;
		cord->y_cur++;
	}
	go_to_cord(cord->x_cur, cord->y_cur, STDIN_FILENO);
}

void	prev_word(char *buf, short len, t_cord *cord)
{
	short	i;

	i = len;
	while (--i >= 0)
	{
		if ((i == 0 || buf[i - 1] == ' ') &&
		(ft_isalpha(buf[i]) || ft_isdigit(buf[i])))
		{
			go_left(len - i, cord);
			break ;
		}
	}
}

void	next_word(char *buf, t_cord *cord)
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
	go_right(i, cord);
}

void	del_symb(char *buf, short len)
{
	buf = ft_strdel_el(buf, len);
	ft_putstr_fd(tigetstr("sc"), STDIN_FILENO);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	ft_putstr_fd(buf + len, STDIN_FILENO);
	ft_putstr_fd(tigetstr("rc"), STDIN_FILENO);
}
