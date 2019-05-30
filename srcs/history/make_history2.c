/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:21:43 by filip             #+#    #+#             */
/*   Updated: 2019/05/30 14:30:45 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void    add_to_historybuf(void)
{
	short	len;
	short	i;

	len = double_arr_len(g_term.history->history_buff);
	if (len >= HISTORY_SIZE)
	{
		i = -1;
		while (++i < len - 1)
			g_term.history->history_buff[i] = g_term.history->history_buff[i + 1];	
		g_term.history->history_buff[len - 1] = g_term.buffer;
	}
	else
	{
		g_term.history->history_buff[len] = g_term.buffer;
		g_term.history->history_buff[++len] = NULL;
	}
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

void	write_history(void)
{
	short	len;

	if (!check_print_arr(g_term.buffer))
		return ;
	add_to_historybuf();
	len = double_arr_len(g_term.history->history_buff);
	len >= HISTORY_SIZE ? add_to_file(len) : rewrite_file(len);
}

void	add_to_file(short len)
{
	int		fd;
	short	i;
	
	if ((fd = open(g_term.home_path, O_RDWR | O_TRUNC)) == -1)
		print_error("42sh", "open() error", NULL, 0);
	i = -1;
	while (++i < len)
	{
		ft_putstr_fd(g_term.history->history_buff[i], fd);
		ft_putchar_fd('\n', fd);
	}
	if (close(fd) == -1)
		print_error("42sh", "close() error", NULL, 0);
}

void	rewrite_file(short len)
{
	int	fd;
	
	if ((fd = open(g_term.home_path, O_RDWR | O_APPEND)) == -1)
		print_error("42sh", "open() error", NULL, 0);
	ft_putstr_fd(g_term.history->history_buff[len - 1], fd);
	ft_putchar_fd('\n', fd);
	if (close(fd) == -1)
		print_error("42sh", "close() error", NULL, 0);
}