/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:00:57 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/25 17:37:16 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			ft_s(t_process *p, t_job *j, pid_t pid)
{
	p->pid = pid;
	if (!j->pgid)
		j->pgid = pid;
	setpgid(pid, j->pgid);
}

static char		**fill_command(t_process *process)
{
	char		**command;
	t_process	*p;
	int			i;

	i = 0;
	p = process;
	while (p)
	{
		p = p->next;
		i++;
	}
	command = (char **)ft_memalloc(sizeof(char *) * i + 10);
	p = process;
	i = 0;
	while (p)
	{
		command[i] = ft_strdup(p->args[0]);
		i++;
		p = p->next;
	}
	return (command);
}

static void		check_builtin(t_job **j)
{
	t_process	*p;

	p = (*j)->first_process;
	while (p)
	{
		if (get_hash_data(g_built_table.table,
					p->args[0], g_built_table.size))
			(*j)->num = -1;
		p = p->next;
	}
}

static void		launch_loop(t_job *j, t_process *p, int foreground)
{
	int			i;
	pid_t		pid;
	int			pipes[2];

	i = 0;
	while (p)
	{
		open_pipe(p, pipes);
		pid = make_process();
		j->pgid = !j->pgid && i == 0 ? pid : j->pgid;
		g_job_pgid = i == 0 ? pid : g_job_pgid;
		if (pid == 0)
			launch_process(p, j->pgid, foreground);
		else
		{
			p->pid = pid;
			ft_s(p, j, pid);
			close_pipes(p);
		}
		i++;
		p = p->next;
	}
}

void			launch_job(t_job *j, int foreground)
{
	char		*last_status;
	t_process	*p;

	check_builtin(&j);
	p = j->first_process;
	j->command = fill_command(p);
	if (!launch_builtin(p, NO_FORK))
	{
		p->completed = 1;
		return ;
	}
	launch_loop(j, p, foreground);
	if (foreground)
		put_job_in_foreground(j, 0);
	else
		put_job_in_background(j, 0);
	set_env("\'?\'", last_status = ft_itoa(g_last_exit_status), ALL_ENV);
	free(last_status);
}
