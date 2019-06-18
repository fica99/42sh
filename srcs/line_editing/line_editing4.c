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
		while (j < len)
			del_symb(buffer->buffer, j++);
	}
	else
	{
		j = len;
		while (j < cord->highlight_pos)
			del_symb(buffer->buffer, j++);
	}
	if (g_flags & TERM_HIGHLIGHT)
		disable_highlight(cord, buffer, len);
}