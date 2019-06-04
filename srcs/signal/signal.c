/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:52:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/04 20:35:34 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	signalling(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGWINCH, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void	signal_handler(int sign)
{
	int	len;

	if (sign == SIGINT || sign == SIGQUIT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (sign == SIGWINCH)
	{
		len = g_term.cord->x_cur - g_term.cord->x_start +
			((g_term.cord->y_cur - g_term.cord->y_start) * g_term.cord->ws_col);
		get_win_size(g_term.cord);
		ft_putstr_fd(tigetstr("clear"), STDIN_FILENO);
		term_prompt();
		get_cur_cord(g_term.cord);
		g_term.cord->x_start = g_term.cord->x_cur;
		g_term.cord->y_start = g_term.cord->y_cur;
		ft_putstr_cord(g_term.buffer, g_term.cord);
		go_left(ft_strlen(g_term.buffer) - len, g_term.cord);
	}
}
