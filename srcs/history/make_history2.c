/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:21:43 by filip             #+#    #+#             */
/*   Updated: 2019/06/08 14:55:47 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void    add_to_historybuf(t_term *term)
{
	short	len;
	short	i;

	len = double_arr_len(term->history->history_buff);
	if (len >= HISTORY_SIZE)
	{
		i = -1;
		while (++i < len - 1)
			term->history->history_buff[i] = term->history->history_buff[i + 1];
		term->history->history_buff[i] = ft_strdup(term->buffer->buffer);
	}
	else
		term->history->history_buff[len++] = ft_strdup(term->buffer->buffer);
	term->history->history_buff[len] = NULL;
}

char	check_print_arr(char *arr)
{
	short	i;

	i = -1;
	while (arr[++i])
	{
		if (ft_isprint(arr[i]) && arr[i] != ' ')
			return (1);
	}
	return (0);
}

void	write_history(t_term *term)
{
	short	len;

	if (!check_print_arr(term->buffer->buffer))
		return ;
	add_to_historybuf(term);
	len = double_arr_len(term->history->history_buff);
	len < HISTORY_SIZE ? add_to_file(len, term->history) : rewrite_file(len, term->history);
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