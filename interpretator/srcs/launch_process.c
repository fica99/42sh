/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:37:26 by filip             #+#    #+#             */
/*   Updated: 2020/02/04 22:26:21 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static void	dup_pipes(t_process *p)
{
	if (p->next && p->next->inpipe)
		if (close(p->next->inpipe) < 0)
			err_exit("42sh", "close() error", NULL, NOERROR);
	if (p->inpipe != STDIN_FILENO)
	{
		if (dup2(p->inpipe, STDIN_FILENO) < 0)
			err_exit("42sh", "dup2() error", NULL, NOERROR);
		if (close(p->inpipe) < 0)
			err_exit("42sh", "close() error", NULL, NOERROR);
	}
	if (p->outpipe != STDOUT_FILENO)
	{
		if (dup2(p->outpipe, STDOUT_FILENO) < 0)
			err_exit("42sh", "dup2() error", NULL, NOERROR);
		if (close(p->outpipe) < 0)
			err_exit("42sh", "close() error", NULL, NOERROR);
	}
}

void	ft_sub(char **args)
{
	while (*args)
	{
		*args = spec_symbols(*args);
		args++;
	}
}

static void	set_sig_def(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
}

static void	prep_proc(pid_t pgid, int foreground, t_process *p)
{
	pid_t	pid;

	pid = getpid();
	setpgid(pid, pgid);
	set_sig_def();
	if (foreground)
		tcsetpgrp(g_shell_terminal, pgid);
	dup_pipes(p);
	if (redir_handle(p) < 0)
		exit(1);
	dup_redir(p->fd_list);
	set_uniq_env(p);
}

void	launch_process(t_process *p, pid_t pgid, int foreground)
{
	prep_proc(pgid, foreground, p);
	if (!launch_builtin(p, FORK))
	{
		p->completed = 1;
		exit(g_last_exit_status);
	}
	else
	{
		ft_sub(p->args);
		if (execve(get_fname(p->args[0]), p->args, g_environ.vars) < 0)
			err_exit("42sh", "permission denied", p->args[0], NOERROR);
		p->completed = 1;
		exit(g_last_exit_status);
	}
}
