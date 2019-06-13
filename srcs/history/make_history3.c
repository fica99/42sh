/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:25:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/13 15:25:46 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	free_history(t_history **history)
{
	char	**buf;

	buf = (*history)->history_buff;
	ft_memdel((void**)&((*history)->history_path));
	free_double_arr(buf);
	ft_memdel((void**)history);
}

void	find_history(char *symbol, t_buff *buffer, t_cord *cord,
t_history *history)
{
	if (!(buffer->history_search))
	{
		if (!(buffer->history_search = ft_strnew(NORMAL_LINE)))
			print_error("42sh", "malloc() error", NULL, ENOMEM);
		buffer->history_search_malloc_len = NORMAL_LINE;
	}
	while (ft_strlen(buffer->history_search) + ft_strlen(symbol) >=
	(size_t)buffer->history_search_malloc_len)
		buffer->history_search = strnew_realloc_buf(buffer->history_search,
		buffer->history_search_malloc_len += NORMAL_LINE);
	ft_putstr_cord(buffer->history_search, cord);
	if (!print_read(symbol, buffer->history_search, cord) && *symbol != CTRL_R)
	{
		g_flags &= ~HISTORY_SEARCH;
		go_to_cord(cord->x_start, cord->y_start, STDIN_FILENO);
		get_cur_cord(cord);
		go_left(17, cord);
		set_start_cord(cord);
		ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
		ft_putstr_cord(buffer->buffer, cord);
		print_move(symbol, buffer, cord, history);
		return ;
	}
	ft_putstr_cord("': ", cord);
	ft_putstr_cord(check_history(history, buffer), cord);
}

char	*check_history(t_history *history, t_buff *buffer)
{
	short	i;

	i = -1;
	while (history->history_buff[++i])
	{
		if (ft_strstr(history->history_buff[i], buffer->history_search) &&
		*(buffer->history_search) != '\0')
		{
			while (ft_strlen(history->history_buff[i]) >=
			(size_t)buffer->malloc_len)
				buffer->buffer = strnew_realloc_buf(buffer->buffer,
				buffer->malloc_len += NORMAL_LINE);
			ft_strclr(buffer->buffer);
			ft_strcat(buffer->buffer, history->history_buff[i]);
			break ;
		}
	}
	return (buffer->buffer);
}
