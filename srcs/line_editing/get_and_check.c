/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:56:18 by filip             #+#    #+#             */
/*   Updated: 2019/06/25 17:29:51 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		get_cur_cord(t_cord *cord)
{
	char	cur_cord[NORMAL_LINE];
	char	*pos;
	short	num;

	num = 0;
	set_input_mode(&(g_term.savetty));
	ft_putstr_fd(tigetstr("u7"), STDIN_FILENO);
	read_handler(cur_cord, STDOUT_FILENO);
	reset_input_mode(&(g_term.savetty));
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
		print_error("42sh", "ioctl() error", NULL, 0);
	cord->ws_col = size.ws_col;
	cord->ws_row = size.ws_row;
}

char	*get_history_file_path(void)
{
	if (ft_getenv("PWD"))
		return (ft_strjoin(ft_getenv("PWD"), "/.history"));
	return (NULL);
}

short	is_start_pos(t_cord *cord)
{
	if ((cord->x_cur == cord->x_start) && (cord->y_cur == cord->y_start))
		return (1);
	return (0);
}
