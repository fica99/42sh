/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_printable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:27:46 by filip             #+#    #+#             */
/*   Updated: 2019/06/24 17:51:47 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	del_symb(char *buf, t_cord *cord)
{
	short	pos;

	buf = ft_strdel_el(buf, cord->pos);
	pos = cord->pos;
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	ft_putstr_cord(buf + cord->pos, cord);
	go_left(cord->pos - pos, cord);
}


void		print_symb(char *c, char *buf, t_cord *cord)
{
	short	pos;

	buf = ft_stradd(buf, c, cord->pos);
	if (*c == '\n')
	{
		cord->pos++;
		return ;
	}
	pos = cord->pos;
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	ft_putstr_cord(buf + cord->pos, cord);
	go_left(cord->pos - pos - ft_strlen(c), cord);
}

void		ft_putstr_cord(char *str, t_cord *cord)
{
	while (str && *str)
	{
		ft_putchar_fd(*str, STDIN_FILENO);
		if (*str == '\n')
		{
			cord->x_cur = 0;
			if (cord->y_cur >= cord->ws_row - 1)
				(cord->y_start)--;
			else
				(cord->y_cur)++;
		}
		else
			(cord->x_cur)++;
		if (cord->x_cur >= cord->ws_col)
		{
			ft_putchar_fd('\n', STDIN_FILENO);
			cord->x_cur = 0;
			if (cord->y_cur >= cord->ws_row - 1)
				(cord->y_start)--;
			else
				(cord->y_cur)++;
		}
		str++;
		cord->pos++;
	}
}
