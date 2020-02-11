/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:05:11 by lcrawn            #+#    #+#             */
/*   Updated: 2020/02/05 16:51:01 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_job	*find_job(int num)
{
	t_job	*j;

	j = g_first_job;
	while (j && j->num != num)
		j = j->next;
	if (j && j->num != -1)
		return (j);
	return (NULL);
}

static t_job	*check_background_process(pid_t pid)
{
	t_job 		*j;
	t_process 	*p;

	j = g_first_job;
	while (j)
	{
		p = j->first_process;
		while (p)
		{
			if (p->pid == pid && j->separator == T_AND)
				return (j);
			p = p->next;
		}
		j = j->next;
	}
	return (0);
}

void			update_status(void)
{
	pid_t pid;
	t_job *j;

	pid = waitpid(WAIT_ANY, &g_last_exit_status, WUNTRACED | WNOHANG);
	if ((j = check_background_process(pid)))
		print_finished_process(j, pid, g_last_exit_status);
	while (!mark_process_status(pid, g_last_exit_status))
	{
		pid = waitpid(WAIT_ANY, &g_last_exit_status, WUNTRACED | WNOHANG);
		if ((j = check_background_process(pid)))
			print_finished_process(j, pid, g_last_exit_status);
	}
}

static void		do_job_notification(t_job *start_job,
		int options, int stop_flag)
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
		else if (j->num > 0 && j->execution)
			format_job_info(j, "running", options);
		if (stop_flag || !j)
			break ;
		else
			j = j->next;
	}
}

void			jobs(int argc, char **argv, char **environ)
{
	(void)environ;
	if (argc == 2)
	{
		if (!ft_strcmp(argv[1], "-l"))
			do_job_notification(g_first_job, EXPAND_INFO, 0);
		else if (!ft_strcmp(argv[1], "-p"))
			do_job_notification(g_first_job, PID_INFO, 0);
		else if (find_job(ft_atoi(argv[1])))
			do_job_notification(find_job(ft_atoi(argv[1])), NO_INFO, 0);
		else
			err("42sh", "jobs", argv[1], "no such job");
	}
	else if (argc == 3)
	{
		if (!find_job(ft_atoi(argv[2])))
			err("42sh", "jobs", argv[2], "no such job");
		else if (!ft_strcmp(argv[1], "-l"))
			do_job_notification(find_job(ft_atoi(argv[2])), EXPAND_INFO, 1);
		else if (!ft_strcmp(argv[1], "-p"))
			do_job_notification(find_job(ft_atoi(argv[2])), PID_INFO, 1);
	}
	else
		do_job_notification(g_first_job, NO_INFO, 0);
}
