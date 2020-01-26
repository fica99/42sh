/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hndl_chld.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 17:30:05 by lcrawn            #+#    #+#             */
/*   Updated: 2020/01/26 18:18:24 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

int			mark_process_status(pid_t pid, int status)
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
				if (WIFSTOPPED(status))
					p->stopped = 1;
				else
					p->completed = 1;
				return (0);
			}
			p = p->next;
		}
		j = j->next;
	}
	return (-1);
}

void		update_status(void)
{
	pid_t pid;

	pid = waitpid(WAIT_ANY, &g_last_exit_status, WUNTRACED | WNOHANG);
	while (!mark_process_status(pid, g_last_exit_status))
		pid = waitpid(WAIT_ANY, &g_last_exit_status, WUNTRACED | WNOHANG);
}

void		wait_for_job(t_job *j)
{
	pid_t pid;

	pid = waitpid(WAIT_ANY, &g_last_exit_status, WUNTRACED);
	while (!mark_process_status(pid, g_last_exit_status)
		&& !job_is_stopped(j)
		&& !job_is_completed(j))
		pid = waitpid(WAIT_ANY, &g_last_exit_status, WUNTRACED);
}

void		do_job_notification(t_job *start_job, int options, int stop_flag)
{
	t_job	*j;

	update_status();
	j = start_job;
	while (j)
	{
		if (job_is_completed(j) && j->num > 0)
		{
			format_job_info(j, "completed", options);
			free_job(&g_first_job, j);
		}
		else if (job_is_stopped(j) && j->num > 0)
			format_job_info(j, "stopped", options);
		else if (j->num > 0)
			format_job_info(j, "running", options);
		if (stop_flag)
			break ;
		if (j)
			j = j->next;
	}
}
