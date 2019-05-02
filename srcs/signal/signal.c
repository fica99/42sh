/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:52:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/30 16:03:10 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

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
		len = g_term.x_cur - g_term.x_start + ((g_term.y_cur - g_term.y_start) * g_term.ws_col);
		get_win_size();
		ft_putstr_fd(HOME, STDIN_FILENO);
		CLEAN_SCREEN(STDIN_FILENO);
		term_prompt();
		get_cur_cord();
		g_term.x_start = g_term.x_cur;
		g_term.y_start = g_term.y_cur;
		ft_putstr_cord(g_term.buffer);
		go_left(ft_strlen(g_term.buffer) - len);
	}
}

