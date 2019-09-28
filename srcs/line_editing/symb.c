/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 19:02:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/28 14:25:50 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	print_symb(char *c, t_line *line)
{
	t_cord	*cord;
	short	pos;
	char	*buf;

	if (ft_isprint(*c))
	{
		cord = line->cord;
		buf = line->buffer.buffer;
		if (g_line_flags & HIGHLIGHT_TEXT)
			disable_highlight(buf, cord);
		pos = cord->pos;
		buf = ft_stradd(buf, c, pos);
		ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
		ft_putstr_cord(buf + pos, cord);
		go_left(cord->pos - pos - ft_strlen(c), cord);
	}
}

void		del_symb(char *buf, t_cord *cord)
{
	short	pos;

	pos = cord->pos;
	buf = ft_strdel_el(buf, pos);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putstr_cord(buf + pos, cord);
	go_left(cord->pos - pos, cord);
}