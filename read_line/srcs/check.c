/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 17:30:00 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/23 16:57:19 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	is_start_pos(t_cord *cord)
{
	if ((cord->x_cur <= cord->x_start) && (cord->y_cur <= cord->y_start))
		return (TRUE);
	return (FALSE);
}

char	is_end_pos(t_cord *cord)
{
	if ((cord->x_cur >= cord->x_end) && (cord->y_cur >= cord->y_end))
		return (TRUE);
	return (FALSE);
}

void	check_malloc_len_buffer(t_buff *buffer, char *c)
{
	while (ft_strlen(buffer->buffer) + ft_strlen(c) >=
			(unsigned)buffer->malloc_len)
		buffer->buffer = ft_strdup_realloc(buffer->buffer,
		buffer->malloc_len += NORMAL_LINE);
}

void	check_end_window(t_cord *cord)
{
	if (cord->y_end >= cord->ws_row - 1)
	{
		--cord->y_cur;
		--cord->y_start;
		--cord->y_end;
	}
}
