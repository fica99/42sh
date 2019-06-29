/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 16:36:39 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/29 10:47:15 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		go_history(char *c, t_history *history, t_line line)
{
	short	len;

	len = double_arr_len(history->history_buff);
	if (((*c == CTRL_R && len) || (g_flags & HISTORY_SEARCH)) && !(g_flags & TERM_QUOTES))
	{
		go_left(line.cord->x_cur - line.cord->x_start + ((line.cord->y_cur -
		line.cord->y_start) * line.cord->ws_col), line.cord);
		ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
		if (!(g_flags & HISTORY_SEARCH))
		{
			ft_putstr_fd("(History search)'", STDIN_FILENO);
			get_cur_cord(line.cord);
			set_start_cord(line.cord);
			g_flags |= HISTORY_SEARCH;
		}
		find_history(c, line, history);
	}
	else if (!(ft_strcmp(c, tigetstr("kcuu1"))) && len)
		history_up(history, line, len);
	else if (!(ft_strcmp(c, tigetstr("kcud1"))) &&
	history->history_index != len)
		history_down(history, line, len);
}

void	find_history(char *symbol, t_line line, t_history *history)
{
	while (ft_strlen(line.history_search.buffer) + ft_strlen(symbol) >=
	(size_t)line.history_search.malloc_len)
		line.history_search.buffer = strnew_realloc_buf(line.history_search.buffer,
		line.history_search.malloc_len += NORMAL_LINE);
	ft_putstr_cord(line.history_search.buffer, line.cord);
	if (!print_printable(symbol, line.history_search.buffer, line.cord) && *symbol != CTRL_R)
	{
		g_flags &= ~HISTORY_SEARCH;
		go_to_cord(line.cord->x_start, line.cord->y_start, STDIN_FILENO);
		unset_start_pos(line.cord);
		get_cur_cord(line.cord);
		go_left(17, line.cord);
		set_start_cord(line.cord);
		line.cord->pos = 0;
		ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
		ft_putstr_cord(line.buffer.buffer, line.cord);
		print_move(symbol, line.buffer.buffer, line.cord);
		return ;
	}
	ft_putstr_fd("': ", STDIN_FILENO);
	get_cur_cord(line.cord);
	line.cord->pos = 0;
	ft_putstr_cord(check_history(history, line.buffer, line.history_search), line.cord);
}

char	*check_history(t_history *history, t_buff buffer, t_buff history_search)
{
	short	i;

	i = -1;
	while (history->history_buff[++i])
	{
		if (ft_strstr(history->history_buff[i], history_search.buffer) &&
		*(history_search.buffer) != '\0')
		{
			while (ft_strlen(history->history_buff[i]) >=
			(size_t)buffer.malloc_len)
				buffer.buffer = strnew_realloc_buf(buffer.buffer,
				buffer.malloc_len += NORMAL_LINE);
			ft_strclr(buffer.buffer);
			ft_strcat(buffer.buffer, history->history_buff[i]);
			break ;
		}
	}
	return (buffer.buffer);
}

void			history_up(t_history *history, t_line line, short len)
{
	go_left(line.cord->x_cur - line.cord->x_start + ((line.cord->y_cur -
	line.cord->y_start) * line.cord->ws_col), line.cord);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	if (--(history->history_index) == len - 1)
	{
		if (!(line.save_buff.buffer = ft_strdup(line.buffer.buffer + line.cord->pos)))
		{
			go_right(ft_strlen(line.buffer.buffer) - line.cord->pos, line.cord);
			ft_putchar_fd('\n', STDERR_FILENO);
			reset_input_mode(&(line.savetty));
			print_error("42sh", "malloc() error", NULL, ENOMEM);
		}
		line.save_buff.malloc_len = ft_strlen(line.buffer.buffer + line.cord->pos);
		ft_strclr(line.buffer.buffer + line.cord->pos);
	}
	else
		ft_strclr(line.buffer.buffer + line.cord->pos);
	while (ft_strlen(history->history_buff[history->history_index]) >=
	(unsigned)line.buffer.malloc_len)
		line.buffer.buffer = strnew_realloc_buf(line.buffer.buffer,
		line.buffer.malloc_len += NORMAL_LINE);
	ft_strcat(line.buffer.buffer + line.cord->pos, history->history_buff[(history->history_index)]);
	ft_putstr_cord(line.buffer.buffer + line.cord->pos, line.cord);
}

void			history_down(t_history *history, t_line line, short len)
{
	go_left(line.cord->x_cur - line.cord->x_start + ((line.cord->y_cur -
	line.cord->y_start) * line.cord->ws_col), line.cord);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	if (++(history->history_index) == len)
	{
		ft_memdel((void**)&(line.buffer.buffer));
		line.buffer.buffer = line.save_buff.buffer;
		line.buffer.malloc_len = line.save_buff.malloc_len;
		line.save_buff.buffer = NULL;
		line.save_buff.malloc_len = 0;
	}
	else
		ft_strclr(line.buffer.buffer + line.cord->pos);
	while (ft_strlen(history->history_buff[(history->history_index)]) >=
	(unsigned)line.buffer.malloc_len)
		line.buffer.buffer = strnew_realloc_buf(line.buffer.buffer,
		line.buffer.malloc_len += NORMAL_LINE);
	ft_strcat(line.buffer.buffer + line.cord->pos, history->history_buff[history->history_index]);
	ft_putstr_cord(line.buffer.buffer + line.cord->pos, line.cord);
}
