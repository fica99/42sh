/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:52:19 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/24 16:59:10 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	set_sig_def(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}

void	sighandler_chld(int sign)
{
	write(STDOUT_FILENO, "\nIM THE CHILD\n", 15);
	if (sign == SIGTSTP)
	{
		pause();
	}
}

void	break_handler(int sign)
{
	if (sign == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (sign == SIGQUIT)
		ft_putstr_fd("\nquit (core dumped)\n", STDERR_FILENO);
}

void	signalling(void)
{
	signal(SIGINT, break_handler);
	signal(SIGQUIT, break_handler);
	signal(SIGWINCH, break_handler);
}
