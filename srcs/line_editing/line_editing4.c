/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:17:45 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/18 17:17:46 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void    cut_highlight(t_buff *buffer, t_cord *cord)
{
	short			len;
	short           j;

	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start)
	* cord->ws_col);
	if ((len - cord->highlight_pos) >= 0)
	{
		j = cord->highlight_pos;
		while (j++ <= len)
			buffer->buffer = ft_strdel_el(buffer->buffer, cord->highlight_pos);
	}
	else
	{
		j = len;
		while (j++ <= cord->highlight_pos)
			buffer->buffer = ft_strdel_el(buffer->buffer, len);
	}
	go_left(len, cord);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	ft_putstr_cord(buffer->buffer, cord);
	if ((len - cord->highlight_pos) < 0)
		go_left(ft_strlen(buffer->buffer) - len, cord);
	else
		go_left(ft_strlen(buffer->buffer) - cord->highlight_pos, cord);
	cord->highlight_pos = 0;
}