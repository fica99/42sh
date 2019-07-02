/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:52:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/07/02 14:46:49 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void signalling(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void signal_handler(int sign)
{
	short len;

	if (sign == SIGINT || sign == SIGQUIT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (sign == SIGWINCH)
	{
		len = g_line.cord->x_cur - g_line.cord->x_start +
			  ((g_line.cord->y_cur - g_line.cord->y_start) * g_line.cord->ws_col);
		reset_input_mode(&(g_line.savetty));
		get_win_size(g_line.cord);
		ft_putstr_fd(tigetstr("clear"), STDIN_FILENO);
		term_prompt();
		get_cur_cord(g_line.cord, 1);
		set_start_cord(g_line.cord);
		g_line.cord->pos = 0;
		ft_putstr_cord(g_line.buffer.buffer, g_line.cord);
		go_left(ft_strlen(g_line.buffer.buffer) - len, g_line.cord);
		set_input_mode(&(g_line.savetty));
	}
}
