/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:52:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/23 22:40:27 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signalling(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGWINCH, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void	signal_handler(int sign)
{
	short	len;

	if (sign == SIGQUIT)
		g_flags |= TERM_SIGQUIT;
	if (sign == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (sign == SIGWINCH)
	{
		len = g_term.x_cur + g_term.y_cur * g_term.ws_col;
		get_win_size();
		if (len / g_term.ws_col)
		{
			go_left(len % g_term.ws_col);
			g_term.x_cur = g_term.prompt_len;
			g_term.y_cur = len / g_term.ws_col;
			while ((g_term.y_cur)-- > 0)
				ft_putstr_fd(PREV_LINE, STDIN_FILENO);
			go_to(g_term.prompt_len);
			g_term.y_cur = 0;
			CLEAN_SCREEN(STDIN_FILENO);
			ft_putstr_cord(g_term.buffer);
				go_left(ft_strlen(g_term.buffer) - len);
		}
		g_flags |= TERM_SIGWINCH;
	}
}

