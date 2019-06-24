/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:57:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/24 16:38:20 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_history		*make_history_buff(void)
{
	int			fd;
	char		**buff;
	short		len;
	t_history	*history;

	if (!(history = (t_history*)malloc(sizeof(t_history))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	history->history_path = get_history_file_path();
	if ((fd = open(history->history_path, O_RDONLY | O_CREAT,
	S_IRUSR | S_IWUSR)) == -1)
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

void	add_to_historybuf(t_term *term)
{
	short	len;
	short	i;

	len = double_arr_len(term->history->history_buff);
	if (len >= HISTORY_SIZE)
	{
		i = -1;
		ft_memdel((void**)&(term->history->history_buff[0]));
		while (++i < len - 1)
			term->history->history_buff[i] = term->history->history_buff[i + 1];
		term->history->history_buff[i] = ft_strdup(term->buffer->buffer);
	}
	else
		term->history->history_buff[len++] = ft_strdup(term->buffer->buffer);
	term->history->history_buff[len] = NULL;
}

void	write_history(t_term *term)
{
	short	len;

	if (!check_print_arr(term->buffer->buffer))
		return ;
	add_to_historybuf(term);
	len = double_arr_len(term->history->history_buff);
	len < HISTORY_SIZE ? add_to_file(len, term->history) :
	rewrite_file(len, term->history);
}

void	rewrite_file(short len, t_history *history)
{
	int		fd;
	short	i;

	if ((fd = open(history->history_path, O_RDWR | O_TRUNC)) == -1)
		print_error("42sh", "open() error", NULL, 0);
	i = -1;
	while (++i < len)
	{
		ft_putstr_fd(history->history_buff[i], fd);
		ft_putchar_fd('\n', fd);
	}
	if (close(fd) == -1)
		print_error("42sh", "close() error", NULL, 0);
}

void	add_to_file(short len, t_history *history)
{
	int	fd;

	if ((fd = open(history->history_path, O_RDWR | O_APPEND)) == -1)
		print_error("42sh", "open() error", NULL, 0);
	ft_putstr_fd(history->history_buff[len - 1], fd);
	ft_putchar_fd('\n', fd);
	if (close(fd) == -1)
		print_error("42sh", "close() error", NULL, 0);
}
