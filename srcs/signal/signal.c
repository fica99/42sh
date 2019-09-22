/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:52:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/22 16:26:28 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	signalling(void)
{
	signal(SIGINT, break_handler);
	signal(SIGQUIT, break_handler);
}

void	break_handler(int sign)
{
	if (sign == SIGINT)
		ft_putstr_fd("\n\n", STDERR_FILENO);
	if (sign == SIGQUIT)
		ft_putstr_fd("\n\nquit (core dumped)\n", STDERR_FILENO);
}

void	win_handler(int sign)
{
	short	pos;

	if (sign == SIGWINCH)
	{
		pos = g_line.cord->pos;
		save_attr(&g_raw_mode);
		get_win_size(g_line.cord);
		ft_putstr_fd(CLEAR_SCREEN, STDIN_FILENO);
		term_prompt(ft_darlen(g_line.history.history_buff), g_argv[0]);
		get_cur_cord(g_line.cord);
		set_start_cord(g_line.cord);
		g_line.cord->pos = 0;
		ft_putstr_cord(g_line.buffer.buffer, g_line.cord);
		go_left(ft_strlen(g_line.buffer.buffer) - pos, g_line.cord);
		set_input_mode(&g_raw_mode);
	}
}
