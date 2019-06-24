/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 16:36:39 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/24 20:07:37 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			go_history(char *c, t_history *history, t_cord *cord,
t_buff *buffer)
{
	short	len;

	len = double_arr_len(history->history_buff);
	if ((*c == CTRL_R && len) || (g_flags & HISTORY_SEARCH))
	{
		go_left(cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start)
		* cord->ws_col), cord);
		cord->pos = 0;
		ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
		if (!(g_flags & HISTORY_SEARCH))
		{
			ft_putstr_fd("(History search)'", STDIN_FILENO);
			get_cur_cord(cord);
			set_start_cord(cord);
			g_flags |= HISTORY_SEARCH;
		}
		find_history(c, buffer, cord, history);
	}
	else if (!(ft_strcmp(c, tigetstr("kcuu1"))) && len)
		history_up(history, cord, len, buffer);
	else if (!(ft_strcmp(c, tigetstr("kcud1"))) &&
	history->history_index != len)
		history_down(history, cord, len, buffer);
}

void	find_history(char *symbol, t_buff *buffer, t_cord *cord,
t_history *history)
{
	if (!(buffer->history_search))
	{
		if (!(buffer->history_search = ft_strnew(buffer->history_search_malloc_len = NORMAL_LINE)))
		{
			go_right(ft_strlen(buffer->buffer) - cord->pos, cord);
			ft_putchar_fd('\n', STDERR_FILENO);
			reset_input_mode(&(g_term.savetty));
			print_error("42sh", "malloc() error", NULL, ENOMEM);
		}
	}
	while (ft_strlen(buffer->history_search) + ft_strlen(symbol) >=
	(size_t)buffer->history_search_malloc_len)
		buffer->history_search = strnew_realloc_buf(buffer->history_search,
		buffer->history_search_malloc_len += NORMAL_LINE);
	cord->pos = 0;
	ft_putstr_cord(buffer->history_search, cord);
	if (!print_printable(symbol, buffer->history_search, cord) && *symbol != CTRL_R)
	{
		g_flags &= ~HISTORY_SEARCH;
		go_to_cord(cord->x_start, cord->y_start, STDIN_FILENO);
		unset_start_pos(cord);
		get_cur_cord(cord);
		go_left(17, cord);
		set_start_cord(cord);
		cord->pos = 0;
		ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
		ft_putstr_cord(buffer->buffer, cord);
		print_move(symbol, buffer, cord);
		return ;
	}
	ft_putstr_fd("': ", STDIN_FILENO);
	get_cur_cord(cord);
	cord->pos = 0;
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

void			history_up(t_history *history, t_cord *cord, short len,
t_buff *buffer)
{
	go_left(cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start)
	* cord->ws_col), cord);
	cord->pos = 0;
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	if (--(history->history_index) == len - 1)
	{
		buffer->save_buff = buffer->buffer;
		buffer->save_malloc_len = buffer->malloc_len;
		buffer->malloc_len = 0;
		buffer->buffer = NULL;
	}
	else
	{
		ft_memdel((void**)&buffer->buffer);
		buffer->malloc_len = 0;
	}
	while (ft_strlen(history->history_buff[history->history_index]) >=
	(unsigned)buffer->malloc_len)
		buffer->buffer = strnew_realloc_buf(buffer->buffer,
		buffer->malloc_len += NORMAL_LINE);
	ft_strcat(buffer->buffer, history->history_buff[(history->history_index)]);
	ft_putstr_cord(buffer->buffer, cord);
}

void			history_down(t_history *history, t_cord *cord, short len,
t_buff *buffer)
{
	go_left(cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start)
	* cord->ws_col), cord);
	cord->pos = 0;
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	if (++(history->history_index) == len)
	{
		ft_memdel((void**)&buffer->buffer);
		buffer->buffer = buffer->save_buff;
		buffer->malloc_len = buffer->save_malloc_len;
		buffer->save_buff = NULL;
		buffer->save_malloc_len = 0;
	}
	else
	{
		ft_memdel((void**)&buffer->buffer);
		buffer->malloc_len = 0;
	}
	while (ft_strlen(history->history_buff[(history->history_index)]) >=
	(unsigned)buffer->malloc_len)
		buffer->buffer = strnew_realloc_buf(buffer->buffer,
		buffer->malloc_len += NORMAL_LINE);
	ft_strcat(buffer->buffer, history->history_buff[history->history_index]);
	ft_putstr_cord(buffer->buffer, cord);
}
