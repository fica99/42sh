/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:57:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/10 19:08:18 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		make_history_buff(t_history *history)
{
	int		fd;
	char	**buff;
	short	len;

	history->history_path = get_history_file_path();
	if ((fd = open(history->history_path, O_RDONLY | O_CREAT,
	S_IRUSR | S_IWUSR)) == -1)
		print_error("42sh", "open() error", NULL, 0);
	len = 0;
	if (ft_getenv("HISTSIZE"))
		history->histsize = ft_atoi(ft_getenv("HISTSIZE"));
	else
		history->histsize = HISTSIZE;
	if (ft_getenv("HISTFILESIZE"))
		history->histfilesize = ft_atoi(ft_getenv("HISTFILESIZE"));
	else
		history->histfilesize = HISTFILESIZE;
	if (!(buff = (char**)malloc(sizeof(char*) * (history->histsize + 1))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	while (len != history->histsize && get_next_line(fd, &(buff[len])) > 0)
		len++;
	buff[len] = NULL;
	if (close(fd) == -1)
		print_error("42sh", "close() error", NULL, 0);
	history->history_buff = buff;
}

void		add_to_historybuf(char *buffer, t_history *history)
{
	short	len;
	short	i;

	len = ft_darlen(history->history_buff);
	if (len >= history->histsize)
	{
		i = -1;
		ft_memdel((void**)&(history->history_buff[0]));
		while (++i < len - 1)
			history->history_buff[i] = history->history_buff[i + 1];
		if (!(history->history_buff[i] = ft_strdup(buffer)))
			print_error("42sh", "malloc() error", NULL, ENOMEM);
	}
	else
	{
		if (!(history->history_buff[len++] = ft_strdup(buffer)))
			print_error("42sh", "malloc() error", NULL, ENOMEM);
	}
	history->history_buff[len] = NULL;
}

void		write_history(char *buffer, t_history *history)
{
	short	len;

	if (!check_print_arr(buffer))
		return ;
	add_to_historybuf(buffer, history);
	len = ft_darlen(history->history_buff);
	len < history->histfilesize ? add_to_file(len, history) :
	rewrite_file(len, history);
}

void		rewrite_file(short len, t_history *history)
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

void		add_to_file(short len, t_history *history)
{
	int		fd;

	if ((fd = open(history->history_path, O_RDWR | O_APPEND)) == -1)
		print_error("42sh", "open() error", NULL, 0);
	ft_putstr_fd(history->history_buff[len - 1], fd);
	ft_putchar_fd('\n', fd);
	if (close(fd) == -1)
		print_error("42sh", "close() error", NULL, 0);
}
