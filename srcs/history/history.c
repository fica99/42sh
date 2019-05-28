/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:57:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/28 23:27:04 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	make_history_buff(void)
{
	int		fd;
	char	**buff;
	short	len;

	if ((fd = open(".history", O_CREAT | O_RDWR)) == -1)
		print_error("42sh", "open() error", NULL, 0);
	len = 0;
	if (!(buff = (char**)malloc(sizeof(char*) * (HISTORY_SIZE + 1))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	while (get_next_line(fd, &(buff[len])) > 0)
	{
		len++;
		if (len == HISTORY_SIZE)
			break;
	}
	buff[len] = NULL;
	if (close(fd) == -1)
		print_error("42sh", "close() error", NULL, 0);
	g_term.history = buff;
}

void	go_history(char *c)
{
	static short	index;
	static short	len;
	char			*cursor;

	if (!len)
		if (!(len = double_arr_len(g_term.history)) || index == 0 || index == len)
			return ;
	cursor = tigetstr("cup");
	if (!(ft_strcmp(c, tigetstr("kcuu1"))))
	{
		if (!index)
			index = len - 1;
		else
			index--;
		ft_putstr_fd(tparm(cursor, g_term.y_start, g_term.x_start), STDIN_FILENO);
		ft_putstr_cord(g_term.history[index]);
	}
	else if (!(ft_strcmp(c, tigetstr("kcud1"))))
	{
		if (index == len)
		{
			ft_putstr_fd(tparm(cursor, g_term.y_start, g_term.x_start), STDIN_FILENO);
			ft_putstr_cord(g_term.buffer);
		}
		else
		{
			ft_putstr_fd(tparm(cursor, g_term.y_start, g_term.x_start), STDIN_FILENO);
			ft_putstr_cord(g_term.history[index]);
		}
	}
}
