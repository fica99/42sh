/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chld_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 17:42:17 by lcrawn            #+#    #+#             */
/*   Updated: 2020/02/12 21:46:38 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static void		sig_handler_other(int sig)
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

static void		child_handler(int sig)
{
	if (sig == SIGSEGV)
		ft_putstr_fd("Segmentation fault: 11\n", STDOUT_FILENO);
	if (sig == SIGABRT)
		ft_putstr_fd("Sigabrt: 6\n", STDOUT_FILENO);
	else if (sig == SIGBUS)
		ft_putstr_fd("Sigbug: 10\n", STDOUT_FILENO);
	else if (sig == SIGCONT)
		ft_putstr_fd("Sigcont: 25\n", STDOUT_FILENO);
	else if (sig == SIGFPE)
		ft_putstr_fd("Sigfpe: 8\n", STDOUT_FILENO);
	else if (sig == SIGHUP)
		ft_putstr_fd("Sighup: 1\n", STDOUT_FILENO);
	else if (sig == SIGTERM)
		ft_putstr_fd("Sigterm: 15\n", STDOUT_FILENO);
	else if (sig == SIGUSR1)
		ft_putstr_fd("Sigusr1: 16\n", STDOUT_FILENO);
	else if (sig == SIGUSR2)
		ft_putstr_fd("Sigusr2: 17\n", STDOUT_FILENO);
	else
		sig_handler_other(sig);
}

void			kill_info(t_process *p, int status, int foreground)
{
	if (!foreground)
	{
		ft_putstr(p->args[0]);
		ft_putstr_fd(": ", STDOUT_FILENO);
	}
	child_handler(status);
}
