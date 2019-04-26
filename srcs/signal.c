/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:52:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/26 21:48:24 by filip            ###   ########.fr       */
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

	if (sign == SIGQUIT)
		g_flags |= TERM_SIGQUIT;
	if (sign == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (sign == SIGWINCH)
	{
		len = ft_strlen(g_term.buffer) - (g_term.x_cur - g_term.x_start + ((g_term.y_cur - g_term.y_start) * g_term.ws_col));
		get_win_size();
		ft_putstr_fd("\033[", STDIN_FILENO);
		ft_putnbr_fd(g_term.y_start, STDIN_FILENO);
		ft_putchar_fd(';', STDIN_FILENO);
		ft_putnbr_fd(g_term.x_start, STDIN_FILENO);
		ft_putchar_fd('H', STDIN_FILENO);
		CLEAN_SCREEN(STDIN_FILENO);
		g_term.x_cur = g_term.x_start;
		g_term.y_cur = g_term.y_start;
		ft_putstr_cord(g_term.buffer);
		go_left(len);
	}
}

