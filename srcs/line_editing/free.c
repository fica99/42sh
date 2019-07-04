/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 21:00:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/07/03 15:36:23 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	free_cord(t_cord **cord)
{
	t_cord	*copy;
	t_cord	*nl;

	if (!*cord)
		return ;
	nl = *cord;
	while (nl)
	{
		copy = nl;
		nl = nl->nl;
		ft_memdel((void**)&copy);
	}
	*cord = NULL;
}

void	unset_start_pos(t_cord *cord)
{
	cord->x_start = 0;
	cord->y_start = 0;
}

void	free_buffer(t_buff *buffer)
{
	if (buffer)
	{
		ft_memdel((void**)&buffer->buffer);
		buffer->malloc_len = 0;
	}
}

void	free_line(t_line *line, t_term *term)
{
	free_buffer(&line->buffer);
	free_buffer(&line->history_search);
	free_buffer(&line->save_buff);
	free_buffer(&line->copy_buff);
	free_cord(&line->cord);
	term->history = line->history;
}
