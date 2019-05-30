/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:57:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/31 01:10:13 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	make_history_buff(void)
{
	int			fd;
	char		**buff;
	short		len;
	t_history	*history;

	if (!(history = (t_history*)malloc(sizeof(t_history*))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	if ((fd = open(g_term.history_path, O_RDONLY | O_CREAT , S_IRUSR | S_IWUSR)) == -1)
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
	history->history_index = double_arr_len(buff);
	g_term.history = history;
}

void	go_history(char *c)
{
	short	len;

	len = double_arr_len(g_term.history->history_buff);
	if (!(ft_strcmp(c, tigetstr("kcuu1"))) && g_term.history->history_index)
		history_up();
	else if (!(ft_strcmp(c, tigetstr("kcud1"))) && g_term.history->history_index != len)
		history_down(len);
}

void		history_up(void)
{
	char	*cursor;

	cursor = tigetstr("cup");
	ft_putstr_fd(tparm(cursor, g_term.y_start, g_term.x_start), STDIN_FILENO);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	g_term.x_cur = g_term.x_start;
	g_term.y_cur = g_term.y_start;
	ft_putstr_cord((g_term.history->history_buff)[--(g_term.history->history_index)]);
}

void		history_down(short len)
{
	char	*cursor;

	cursor = tigetstr("cup");
	ft_putstr_fd(tparm(cursor, g_term.y_start, g_term.x_start), STDIN_FILENO);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	g_term.x_cur = g_term.x_start;
	g_term.y_cur = g_term.y_start;
	if (++(g_term.history->history_index) == len)
		ft_putstr_cord(g_term.buffer);
	else
		ft_putstr_cord(g_term.history->history_buff[g_term.history->history_index]);
}

void		change_buf(void)
{
	short	len;

	len = double_arr_len(g_term.history->history_buff);
	if (g_flags)
	{
		g_term.history->history_index = len;
		return ;
	}
	if (g_term.history->history_index != len)
	{
		ft_memdel((void**)&g_term.buffer);
		g_term.buffer = ft_strdup(g_term.history->history_buff[g_term.history->history_index]);
	}
	if (len >= HISTORY_SIZE)
		g_term.history->history_index = len;
	else
	{
		if (check_print_arr(g_term.buffer))
			g_term.history->history_index = ++len;
	}
}