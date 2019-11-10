/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_cord.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:37:01 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/10 15:14:39 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void		rl_get_cur_cord(t_rl_cord *cord)
{
	char	cur_cord[LINE_MAX + 1];
	char	*pos;
	short	num;

	num = 0;
	ft_putstr_fd(RL_CUR_CORD, STDIN_FILENO);
	rl_read_handler(cur_cord, STDOUT_FILENO);
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

void		rl_get_win_size(t_rl_cord *cord)
{
	struct winsize	size;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < 0)
		rl_err("42sh", "ioctl() error", UNDEFERR);
	cord->ws_col = size.ws_col;
	cord->ws_row = size.ws_row;
}

void		rl_set_start_cord(t_rl_cord *cord)
{
	cord->x_start = cord->x_cur;
	cord->y_start = cord->y_cur;
}

void		rl_set_end_cord(t_rl_cord *cord)
{
	cord->x_end = cord->x_cur;
	cord->y_end = cord->y_cur;
}

void		rl_start_cord_data(t_rl_cord *cord)
{
	rl_get_cur_cord(cord);
	rl_get_win_size(cord);
	rl_set_start_cord(cord);
	rl_set_end_cord(cord);
}
