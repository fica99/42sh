/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_jobs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 17:32:51 by lcrawn            #+#    #+#             */
/*   Updated: 2020/02/04 22:36:55 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static void		init_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}

void			init_jobs(void)
{
	g_first_job = NULL;
	g_last_job = NULL;
	g_shell_terminal = STDIN_FILENO;
	init_signals();
	g_shell_pgid = getpid();
	tcgetattr(g_shell_terminal, &g_shell_tmodes);
}
