/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:22:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/25 18:57:41 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	free_line(t_line *line)
{
	free_buffer(&line->buffer);
	free_buffer(&line->history_search);
	free_buffer(&line->save_buff);
	free_buffer(&line->copy_buff);
	free_buffer(&line->her_buff);
	ft_memdel((void**)&line->cord);
	line->templates = free_hash_table(line->templates, TEMPL_TABLE_SIZE,
	DONT_FREE_TABLE_DATA);
}

void	free_buffer(t_buff *buffer)
{
	if (buffer)
	{
		ft_memdel((void**)&buffer->buffer);
		buffer->malloc_len = 0;
	}
}
