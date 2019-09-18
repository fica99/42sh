/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:32:36 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/18 20:57:18 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	set_data(t_line *line)
{
	g_line_flags = INIT_FLAGS;
	get_win_size(line->cord);
	get_cur_cord(line->cord);
	set_start_cord(line->cord);
}

void		get_cur_cord(t_cord *cord)
{
	char	cur_cord[LINE_MAX + 1];
	char	*pos;
	short	num;

	num = 0;
	ft_putstr_fd(CUR_CORD, STDIN_FILENO);
	read_handler(cur_cord, STDOUT_FILENO);
	if (!(pos = ft_strchr(cur_cord, (int)'[')))
		return ;
	while (ft_isdigit(*(++pos)))
		num = num * 10 + (int)*pos - 48;
	cord->y_cur = num - 1;
	num = 0;
	if (!(pos = ft_strchr(cur_cord, (int)';')))
		return ;
	while (ft_isdigit(*(++pos)))
		num = num * 10 + (int)*pos - 48;
	cord->x_cur = num - 1;
}

void		get_win_size(t_cord *cord)
{
	struct winsize	size;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) < 0)
		err_exit("42sh", "ioctl() error", NULL, 0);
	cord->ws_col = size.ws_col;
	cord->ws_row = size.ws_row;
}

void		unset_cord(t_cord *cord)
{
	free_cord(&cord->nl);
	cord->x_cur = 0;
	cord->x_start = 0;
	cord->ws_col = 0;
	cord->ws_row = 0;
	cord->y_cur = 0;
	cord->y_start = 0;
	cord->pos = 0;
	cord->highlight_pos = 0;
}

void		unset_data(t_line *line)
{
	unset_cord(line->cord);
	ft_strclr(line->buffer.buffer);
	ft_strclr(line->save_buff.buffer);
	ft_strclr(line->stop_buff.buffer);
	ft_strclr(line->history_search.buffer);
}
