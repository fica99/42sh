/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 16:36:39 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/01 21:21:25 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		go_history(char *c, t_line *line)
{
	short	len;

	len = ft_darlen(line->history.history_buff);
	if (((*c == CTRL_R && len) || (g_line_flags & HISTORY_SEARCH)) &&
	!(g_line_flags & TERM_QUOTES))
	{
		go_to_cord(line->cord->x_start, line->cord->y_start, STDIN_FILENO);
		ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
		if (!(g_line_flags & HISTORY_SEARCH))
		{
			ft_putstr_fd("(History search)'", STDIN_FILENO);
			g_line_flags |= HISTORY_SEARCH;
		}
		get_cur_cord(line->cord);
		set_start_cord(line->cord);
		line->cord->pos = 0;
		find_history(c, line);
	}
	if (!(ft_strcmp(c, tigetstr("kcuu1"))) && len &&
	line->history.history_index)
		history_up(line, len);
	else if (!(ft_strcmp(c, tigetstr("kcud1"))) &&
	line->history.history_index != len)
		history_down(line, len);
}

void		find_history(char *symbol, t_line *line)
{
	check_malloc_len_buffer(&line->history_search, symbol);
	ft_putstr_cord(line->history_search.buffer, line->cord);
	if (!print_printable(symbol, line->history_search.buffer, line->cord) &&
	*symbol != CTRL_R)
	{
		g_line_flags &= ~HISTORY_SEARCH;
		unset_start_pos(line->cord);
		go_left(line->cord->pos + 17, line->cord);
		set_start_cord(line->cord);
		line->cord->pos = 0;
		ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
		ft_putstr_cord(line->buffer.buffer, line->cord);
		ft_strclr(line->history_search.buffer);
		if (!print_move(symbol, line->buffer.buffer, line->cord))
			print_symbols(symbol, line);
		return ;
	}
	ft_putstr_fd("': ", STDIN_FILENO);
	get_cur_cord(line->cord);
	line->cord->pos = 0;
	ft_putstr_cord(check_history(&line->history, &line->buffer,
	&line->history_search), line->cord);
}

char		*check_history(t_history *history, t_buff *buffer,
t_buff *history_search)
{
	short	i;

	i = -1;
	while (history->history_buff[++i])
	{
		if (ft_strstr(history->history_buff[i], history_search->buffer) &&
		*(history_search->buffer) != '\0')
		{
			check_malloc_len_buffer(buffer, history->history_buff[i]);
			ft_strclr(buffer->buffer);
			ft_strcat(buffer->buffer, history->history_buff[i]);
			break ;
		}
	}
	return (buffer->buffer);
}

void		history_up(t_line *line, short len)
{
	go_left(line->cord->pos, line->cord);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	if (--(line->history.history_index) == len - 1)
		ft_strcat(line->save_buff.buffer, line->buffer.buffer +
		line->cord->pos);
	ft_strclr(line->buffer.buffer + line->cord->pos);
	check_malloc_len_buffer(&line->buffer,
	line->history.history_buff[line->history.history_index]);
	ft_strcat(line->buffer.buffer, line->history.history_buff[(line->
	history.history_index)]);
	ft_putstr_cord(line->buffer.buffer + line->cord->pos, line->cord);
}

void		history_down(t_line *line, short len)
{
	char	*history_buffer;

	go_left(line->cord->pos, line->cord);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	if (++(line->history.history_index) == len)
		history_buffer = line->save_buff.buffer;
	else
		history_buffer = line->history.history_buff[(line->
		history.history_index)];
	ft_strclr(line->buffer.buffer + line->cord->pos);
	check_malloc_len_buffer(&line->buffer, history_buffer);
	ft_strcat(line->buffer.buffer, history_buffer);
	ft_putstr_cord(line->buffer.buffer + line->cord->pos, line->cord);
	if (line->history.history_index == len)
		ft_strclr(line->save_buff.buffer);
}
