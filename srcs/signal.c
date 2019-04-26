/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:52:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/27 01:36:54 by filip            ###   ########.fr       */
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
	int	len;

	if (sign == SIGINT || sign == SIGQUIT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (sign == SIGWINCH)
	{
		len = ft_strlen(g_term.buffer) - (g_term.x_cur - g_term.x_start + ((g_term.y_cur - g_term.y_start) * g_term.ws_col));
		get_win_size();
		HOME(STDIN_FILENO);
		CLEAN_SCREEN(STDIN_FILENO);
		term_prompt();
		get_cur_cord();
		g_term.x_start = g_term.x_cur;
		g_term.y_start = g_term.y_cur;
		ft_putstr_cord(g_term.buffer);
		go_left(len);
	}
}

