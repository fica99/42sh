/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:00:57 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/18 22:15:39 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static int		check_builtin(t_job **j)
{
	t_process	*p;
	int			builtin;

	builtin = 0;
	p = (*j)->first_process;
	while (p)
	{
		if (get_hash_data(g_builtins_hash_table.table,
					p->args[0], g_builtins_hash_table.size))
		{
			builtin++;
			(*j)->num = -1;
		}
		p = p->next;
	}
	return (builtin);
}

static pid_t	make_process(void)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		err_exit("42sh", "dup() error", NULL, NOERROR);
	return (pid);
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
			clean_proc(p, j, pid);
		i++;
		p = p->next;
	}
}

void			cls_redir(int **red)
{
	int *tmp;

	while (*red)
	{
		tmp = *red;
		if (*tmp > 2)
			close(*tmp);
		if (*++tmp > 2)
			close(*tmp);
		red++;
	}
}

void			launch_job(t_job *j, int foreground)
{
	char		*last_status;
	t_process	*p;

	if (redir_handle(j) < 0 || !process_substitutions(j))
		return ;
	check_builtin(&j);
	p = j->first_process;
	if (!launch_no_fork_builtin(p))
	{
		p->completed = 1;
		cls_redir(p->fd_list);
		g_last_exit_status = g_last_exit_status == 256 ? 1 : g_last_exit_status;
		set_var("?", last_status = ft_itoa(g_last_exit_status), ALL_VARS);
		free(last_status);
		return ;
	}
	launch_loop(j, p, foreground);
	if (foreground)
		put_job_in_foreground(j, 0);
	else
		put_job_in_background(j, 0);
	mark_exit_stat(j);
	g_last_exit_status = fix_exit(g_last_exit_status);
	set_var("?", last_status = ft_itoa(g_last_exit_status), ALL_VARS);
	free(last_status);
}
