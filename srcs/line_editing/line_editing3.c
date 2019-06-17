/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 19:35:43 by filip             #+#    #+#             */
/*   Updated: 2019/06/17 16:08:03 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_shell.h"

void		highlight_right(t_buff *buffer, t_cord *cord, short pos)
{
    short			len;

	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start)
	* cord->ws_col);
	go_left(len, cord);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	if (pos >= len + 1)
		ft_putstr_highlight(buffer->buffer, len + 1,  pos, cord);
	else
		ft_putstr_highlight(buffer->buffer, pos,  len + 1, cord);
	go_left(ft_strlen(buffer->buffer) - (len + 1), cord);
}

void		disable_highlight(t_cord *cord, t_buff *buffer, short len)
{
	g_flags &= ~TERM_HIGHLIGHT;
	buffer->highlight_pos = 0;
	go_left(len, cord);
	ft_putstr_cord(buffer->buffer, cord);
	go_left(ft_strlen(buffer->buffer) - len, cord);
}