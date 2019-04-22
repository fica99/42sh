/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:52:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/22 16:28:45 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

  void	signalling(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGWINCH, sigwinch_handler);
	signal(SIGQUIT, signal_handler);
}

void	signal_handler(int sign)
{
	if (sign == SIGQUIT)
		g_flags |= SHELL_SIGQUIT;
	if (sign == SIGINT)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		ft_strclr(buffer);
		shell_prompt();
		g_flags |= SHELL_SIGINT;
	}
}

void	sigwinch_handler(int sign)
{
	short	len;
	short	n;

	if (sign == SIGWINCH)
	{
		g_flags |= SHELL_SIGWINCH;
		len = cord.x_cur + cord.y_cur * cord.ws_col;
		get_cord();
		n = 0;
		while (len / cord.ws_col - (n++) > 0)
			ft_putstr_fd(PREV_LINE, STDIN_FILENO);
		if (len <= cord.ws_col)
			go_left(len);
		go_to(cord.prompt);
		cord.x_cur = cord.prompt;
		cord.y_cur = 0;
		CLEAN_SCREEN(STDIN_FILENO);
		ft_putstr_cord(buffer);
		go_left(ft_strlen(buffer) - len + 1);
	}
}

