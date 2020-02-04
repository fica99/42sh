/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hndl_chld.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 17:30:05 by lcrawn            #+#    #+#             */
/*   Updated: 2020/02/04 21:45:50 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static void		mark_process_pid(t_process **p, int status)
{
	if (WIFSTOPPED(status))
	{
		(*p)->stopped = 1;
		err("42sh", "suspended", (*p)->args[0], NOERROR);
	}
	else
		(*p)->completed = 1;
}

static int		mark_process_status(pid_t pid, int status)
{
	t_job		*j;
	t_process	*p;

	if (pid <= 0)
		return (-1);
	j = g_first_job;
	while (j)
	{
		p = j->first_process;
		while (p)
		{
			if (p->pid == pid)
			{
				mark_process_pid(&p, status);
				return (0);
			}
			p = p->next;
		}
		j = j->next;
	}
	return (-1);
}

static void		set_exit_status(pid_t pid, t_job *j, int status)
{
	t_process *p;

	p = j->first_process;
	while (p)
	{
		if (p->pid == pid)
		{
			p->exit_status = status;
			return ;
		}
		p = p->next;
	}
}

void			wait_for_job(t_job *j)
{
	pid_t pid;

	pid = waitpid(WAIT_ANY, &g_last_exit_status, WUNTRACED);
	set_exit_status(pid, j, g_last_exit_status);
	while (!mark_process_status(pid, g_last_exit_status)
		&& !job_is_stopped(j)
		&& !job_is_completed(j))
	{
		pid = waitpid(WAIT_ANY, &g_last_exit_status, WUNTRACED);
		set_exit_status(pid, j, g_last_exit_status);
	}
}
