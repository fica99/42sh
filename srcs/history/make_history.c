/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:57:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/11 21:23:28 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_history	*make_history_buff(void)
{
	int			fd;
	char		**buff;
	short		len;
	t_history	*history;

	if (!(history = (t_history*)malloc(sizeof(t_history))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	history->history_path = get_history_file_path();
	if ((fd = open(history->history_path, O_RDONLY | O_CREAT , S_IRUSR
	| S_IWUSR)) == -1)
		print_error("42sh", "open() error", NULL, 0);
	len = 0;
	if (!(buff = (char**)malloc(sizeof(char*) * (HISTORY_SIZE + 1))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	while (len != HISTORY_SIZE && get_next_line(fd, &(buff[len])) > 0)
		len++;
	buff[len] = NULL;
	if (close(fd) == -1)
		print_error("42sh", "close() error", NULL, 0);
	history->history_buff = buff;
	history->history_index = len;
	return (history);
}

void	go_history(char *c, t_history *history, t_cord *cord, t_buff *buffer)
{
	short		len;

	len = double_arr_len(history->history_buff);
	if (!(ft_strcmp(c, tigetstr("kcuu1"))) && history->history_index)
		history_up(history, cord, len, buffer);
	else if (!(ft_strcmp(c, tigetstr("kcud1"))) && history->history_index != len)
		history_down(history, cord, len, buffer);
//	else if (*c == CTRL_R && len)
//		find_history();
}

void		history_up(t_history *history, t_cord *cord, short len, t_buff *buffer)
{
	go_to_cord(cord->x_start, cord->y_start, STDIN_FILENO);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	cord->x_cur = cord->x_start;
	cord->y_cur = cord->y_start;
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
	while (ft_strlen(history->history_buff[history->history_index]) >= (unsigned)buffer->malloc_len)
			buffer->buffer = strnew_realloc_buf(buffer->buffer, buffer->malloc_len += NORMAL_LINE);
	ft_strcat(buffer->buffer, history->history_buff[(history->history_index)]);
	ft_putstr_cord(buffer->buffer, cord);
}

void		history_down(t_history *history, t_cord *cord, short len, t_buff *buffer)
{
	go_to_cord(cord->x_start, cord->y_start, STDIN_FILENO);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	cord->x_cur = cord->x_start;
	cord->y_cur = cord->y_start;
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
	while (ft_strlen(history->history_buff[(history->history_index)]) >= (unsigned)buffer->malloc_len)
		buffer->buffer = strnew_realloc_buf(buffer->buffer, buffer->malloc_len += NORMAL_LINE);
	ft_strcat(buffer->buffer, history->history_buff[(history->history_index)]);
	ft_putstr_cord(buffer->buffer, cord);
}
