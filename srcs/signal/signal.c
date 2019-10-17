/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:52:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/17 16:41:13 by aashara-         ###   ########.fr       */
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
		ft_putstr_fd("\n\nquit (core dumped)\n\n", STDERR_FILENO);
}

void	win_handler(int sign)
{
	short	pos;
	char	*ps1;

	if (sign == SIGWINCH)
	{
		pos = g_line.cord->pos;
		save_attr(&g_raw_mode);
		get_win_size(g_line.cord);
		ft_putstr_fd(CLEAR_SCREEN, STDIN_FILENO);
		if (!(ps1 = ft_getenv("PS1")))
			standart_prompt();
		else
			write_prompt(ps1);
		get_cur_cord(g_line.cord);
		set_start_cord(g_line.cord);
		set_end_cord(g_line.cord);
		g_line.cord->pos = 0;
		ft_putstr_cord(g_line.buffer.buffer, g_line.cord);
		go_left(ft_strlen(g_line.buffer.buffer + pos), g_line.cord);
		set_input_mode(&g_raw_mode);
	}
}
