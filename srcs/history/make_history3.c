/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:25:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/12 19:52:21 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void    free_history(t_history **history)
{
	char    	**buf;

	buf = (*history)->history_buff;
	ft_memdel((void**)&((*history)->history_path));
	free_double_arr(buf);
	ft_memdel((void**)history);
}

void	find_history(char *symbol, t_buff *buffer, t_cord *cord, t_history *history)
{
	short	i;
	if (!(buffer->history_search))
	{
		if (!(buffer->history_search = ft_strnew(NORMAL_LINE)))
			print_error("42sh", "malloc() error", NULL, ENOMEM);
		buffer->history_search_malloc_len = NORMAL_LINE;
	}
	ft_putstr_cord(buffer->history_search, cord);
	print_read(symbol, buffer->history_search, cord);
	ft_putstr_cord("': ", cord);
	i = -1;
	while (history->history_buff[++i])
	{
		if (ft_strstr(history->history_buff[i], buffer->history_search) && *(buffer->history_search) != '\0')
		{
			while (ft_strlen(history->history_buff[i]) >= (size_t)buffer->malloc_len)
				buffer->buffer = strnew_realloc_buf(buffer->buffer, buffer->malloc_len += NORMAL_LINE);
			ft_strclr(buffer->buffer);
			ft_strcat(buffer->buffer, history->history_buff[i]);
			break;
		}
	}
	ft_putstr_cord(buffer->buffer, cord);
}