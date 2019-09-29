/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 19:02:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/29 20:18:41 by aashara-         ###   ########.fr       */
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
		line->buffer.buffer = ft_stradd(buf, c, pos);
		ft_putstr_fd(SAVE_CUR, STDIN_FILENO);
		ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
		ft_putstr_cord(buf + pos, cord);
		go_left(cord->pos - pos, cord);
		ft_putstr_fd(RESTORE_CUR, STDIN_FILENO);
		go_right(ft_strlen(c), cord);
	}
}

void		del_symb(char *buf, t_cord *cord)
{
	short	pos;

	pos = cord->pos;
	buf = ft_strdel_el(buf, pos);
	ft_putstr_fd(SAVE_CUR, STDIN_FILENO);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putstr_cord(buf + cord->pos, cord);
	go_left(cord->pos - pos, cord);
	ft_putstr_fd(RESTORE_CUR, STDIN_FILENO);
}
