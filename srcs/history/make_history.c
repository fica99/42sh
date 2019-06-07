/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:57:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/07 22:36:49 by filip            ###   ########.fr       */
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
	history->history_index = double_arr_len(buff);
	return (history);
}

void	go_history(char *c, t_history *history, t_cord *cord, char *buffer)
{
	short		len;

	len = double_arr_len(history->history_buff);
	if (!(ft_strcmp(c, tigetstr("kcuu1"))) && history->history_index)
		history_up(history, cord);
	else if (!(ft_strcmp(c, tigetstr("kcud1"))) && history->history_index != len)
		history_down(history, cord, len, buffer);
//	else if (*c == CTRL_R && len)
//		find_history();
}

void		history_up(t_history *history, t_cord *cord)
{
	char	*cursor;

	cursor = tigetstr("cup");
	ft_putstr_fd(tparm(cursor, cord->y_start, cord->x_start), STDIN_FILENO);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	cord->x_cur = cord->x_start;
	cord->y_cur = cord->y_start;
	ft_putstr_cord((history->history_buff)[--(history->history_index)], cord);
}

void		history_down(t_history *history, t_cord *cord, short len, char *buffer)
{
	char	*cursor;

	cursor = tigetstr("cup");
	ft_putstr_fd(tparm(cursor, cord->y_start, cord->x_start), STDIN_FILENO);
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	cord->x_cur = cord->x_start;
	cord->y_cur = cord->y_start;
	if (++(history->history_index) == len)
		ft_putstr_cord(buffer, cord);
	else
		ft_putstr_cord(history->history_buff[history->history_index], cord);
}

void		change_buf(t_history *history, char **buffer)
{
	short	len;
	char	*buff;

	len = double_arr_len(history->history_buff);
	if (g_flags)
	{
		history->history_index = len;
		return ;
	}
	if (history->history_index != len)
	{
		buff = *buffer;
		ft_memdel((void**)&buff);
		*buffer = ft_strdup(history->history_buff[history->history_index]);
	}
	if (len >= HISTORY_SIZE)
		history->history_index = len;
	else
		if (check_print_arr(*buffer))
			history->history_index = ++len;
}