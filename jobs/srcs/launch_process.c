/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara <aashara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:37:26 by filip             #+#    #+#             */
/*   Updated: 2020/01/26 21:00:29 by aashara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

void	dup_pipes(t_process *p)
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

void	prep_proc(pid_t pgid, int foreground, t_process *p)
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
		if (execve(get_fname(p->args[0]), p->args, g_env.env) < 0)
			err_exit("42sh", "permission denied", p->args[0], NOERROR);
		p->completed = 1;
		exit(g_last_exit_status);
	}
}
