/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:52:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/27 22:55:25 by aashara-         ###   ########.fr       */
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
	t_cord	*cord;

	if (sign == SIGWINCH)
	{
		cord = g_line.cord;
		cord->pos -= (cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start) *
		cord->ws_col));
		set_attr(&g_orig_mode);
		get_win_size(g_line.cord);
		go_to_cord(0, g_line.cord->y_start, STDIN_FILENO);
		ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
		write_prompt(g_prompt);
		ft_putstr_cord(g_line.buffer.buffer + cord->pos, cord);
	}
}
