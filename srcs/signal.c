/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:52:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/19 12:52:36 by aashara-         ###   ########.fr       */
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
	if (sign == SIGQUIT)
		g_flags |= SHELL_SIGQUIT;
	if (sign == SIGWINCH)
		get_cord();
	if (sign == SIGINT)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		g_flags |= SHELL_SIGINT;
		shell_prompt();
	}
}

