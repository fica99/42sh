/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:00:57 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/21 16:00:59 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	close_pipes(t_process *p)
{
	if (p->inpipe != STDIN_FILENO)
		if (close(p->inpipe) < 0)
			err_exit("42sh", "close() error", NULL, NOERROR);
	if (p->outpipe != STDOUT_FILENO)
		if (close(p->outpipe) < 0)
			err_exit("42sh", "close() error", NULL, NOERROR);
}

void	open_pipe(t_process *p, int *pipes)
{
	if (p->next)
	{
		if (pipe(pipes) < 0)
			err_exit("42sh", "pipe() error", NULL, NOERROR);
		p->outpipe = pipes[1];
		p->next->inpipe = pipes[0];
	}
}

void	ft_s(t_process *p, t_job *j, pid_t pid)
{
	p->pid = pid;
	if (g_shell_is_interactive)
	{
		if (!j->pgid)
			j->pgid = pid;
		setpgid(pid, j->pgid);
	}
}

void	launch_job(t_job *j, int foreground)
{
	char		*last_status;
	t_process	*p;
	pid_t		pid;
	int			pipes[2];

	p = j->first_process;
	if (!launch_builtin(p, NO_FORK))
		return ;
	while (p)
	{
		open_pipe(p, pipes);
		pid = make_process();
		if (pid == 0)
			launch_process(p, j->pgid, foreground);
		else
		{
			ft_s(p, j, pid);
			close_pipes(p);
		}
		p = p->next;
	}
	while (waitpid(-1, &g_last_exit_status, 0) != -1)
		;
	set_env("?", last_status = ft_itoa(g_last_exit_status), ALL_ENV);
	free(last_status);
}
