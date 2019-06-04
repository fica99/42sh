/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:29:29 by filip             #+#    #+#             */
/*   Updated: 2019/06/02 15:09:48 by filip            ###   ########.fr       */
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
