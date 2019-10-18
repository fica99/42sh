/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cord.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 21:23:00 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/18 19:51:35 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_shell.h"

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

void		unset_cord(t_cord *cord)
{
	cord->x_cur = 0;
	cord->x_start = 0;
	cord->ws_col = 0;
	cord->ws_row = 0;
	cord->y_cur = 0;
	cord->y_start = 0;
	cord->pos = 0;
	cord->x_end = 0;
	cord->y_end = 0;
	cord->highlight_pos = 0;
}

void		get_win_size(t_cord *cord)
{
	struct winsize	size;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) < 0)
		err_exit(g_argv[0], "ioctl() error", NULL, 0);
	cord->ws_col = size.ws_col;
	cord->ws_row = size.ws_row;
}

void	set_start_cord(t_cord *cord)
{
	cord->x_start = cord->x_cur;
	cord->y_start = cord->y_cur;
}

void	set_end_cord(t_cord *cord)
{
	cord->x_end = cord->x_cur;
	cord->y_end = cord->y_cur;
}
