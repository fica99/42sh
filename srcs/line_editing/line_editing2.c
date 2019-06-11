/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:29:29 by filip             #+#    #+#             */
/*   Updated: 2019/06/11 18:49:39 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			print_symb(char *c, char *buf, short len, t_cord * cord)
{
	short	i;

	buf = ft_stradd(buf, c, len);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	ft_putstr_cord(buf + len, cord);
	i = ft_strlen(buf + len) - 1;
	go_left(i, cord);
}

void			go_to_cord(short x, short y, int fd)
{
	char	*cursor;

	cursor = tigetstr("cup");
	ft_putstr_fd(tparm(cursor, y, x), fd);
}
