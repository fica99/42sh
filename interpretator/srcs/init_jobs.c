/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_jobs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 17:32:51 by lcrawn            #+#    #+#             */
/*   Updated: 2020/02/10 18:33:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static void		sig_handler_2(int sig)
{
	if (sig == SIGPROF)
		ft_putstr_fd("Sigprof: 29\n", STDOUT_FILENO);
	else if (sig == SIGSYS)
		ft_putstr_fd("Sigsys: 12\n", STDOUT_FILENO);
	else if (sig == SIGTRAP)
		ft_putstr_fd("Sigtrap: 5\n", STDOUT_FILENO);
	else if (sig == SIGURG)
		ft_putstr_fd("Sigurg: 21\n", STDOUT_FILENO);
	else if (sig == SIGVTALRM)
		ft_putstr_fd("Sigvtalrm: 28\n", STDOUT_FILENO);
	else if (sig == SIGXCPU)
		ft_putstr_fd("Sigxcpu: 30\n", STDOUT_FILENO);
	else if (sig == SIGXFSZ)
		ft_putstr_fd("Sigxfsz: 31\n", STDOUT_FILENO);
}

static void		sig_handler(int sig)
{
	sig = WTERMSIG(g_last_exit_status);
	if (sig == SIGSEGV)
		ft_putstr_fd("Segmentation fault: 11\n", STDOUT_FILENO);
	else if (sig == SIGABRT)
		ft_putstr_fd("Sigabrt: 6\n", STDOUT_FILENO);
	else if (sig == SIGBUS)
		ft_putstr_fd("Sigbug: 10\n", STDOUT_FILENO);
	else if (sig == SIGCONT)
		ft_putstr_fd("Sigcont: 25\n", STDOUT_FILENO);
	else if (sig == SIGFPE)
		ft_putstr_fd("Sigfpe: 8\n", STDOUT_FILENO);
	else if (sig == SIGHUP)
		ft_putstr_fd("Sighup: 1\n", STDOUT_FILENO);
	else if (sig == SIGPIPE)
		ft_putstr_fd("Sigpipe: 13\n", STDOUT_FILENO);
	else if (sig == SIGTERM)
		ft_putstr_fd("Sigterm: 15\n", STDOUT_FILENO);
	else if (sig == SIGUSR1)
		ft_putstr_fd("Sigusr1: 16\n", STDOUT_FILENO);
	else if (sig == SIGUSR2)
		ft_putstr_fd("Sigusr2: 17\n", STDOUT_FILENO);
	else
		sig_handler_2(sig);
}

static void		init_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, sig_handler);
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
