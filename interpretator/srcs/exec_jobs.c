/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_jobs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:23:13 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/14 02:14:16 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static char			**fill_command(t_process *process)
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
	if (!(command = ft_darnew(i)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
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

void				mark_exit_stat(t_job *j)
{
	t_process *p;

	p = j->first_process;
	while (p->next)
		p = p->next;
	if (p->error != 0)
		g_last_exit_status = 256;
}

static int			log_check(t_job *j, t_job *last_job)
{
	t_process	*p;
	int			separator;
	int			j_amount;
	int			bad_exit;

	if (j == last_job || last_job->separator == 0)
		return (0);
	bad_exit = 0;
	j_amount = 0;
	separator = j->separator;
	while (j && j != last_job)
	{
		p = j->first_process;
		while (p && p->next)
			p = p->next;
		if ((p && p->exit_status) || !j->execution)
			bad_exit++;
		separator = j->next == last_job ? j->separator : separator;
		j_amount++;
		j = j->next;
	}
	if (j && (separator == 0 || ((separator == T_AND_AND && bad_exit < j_amount)
	|| (separator == T_OR_OR && bad_exit == j_amount))))
		return (0);
	return (-1);
}

void				exec_jobs(void)
{
	t_job	*j;
	t_job	*first_job;

	if (!g_last_job || !g_last_job->next)
		j = g_first_job;
	else
	{
		g_last_job = g_last_job->next;
		j = g_last_job;
	}
	first_job = j;
	while (j)
	{
		g_last_job = j;
		j->command = !j->command ? fill_command(j->first_process) : j->command;
		if (!log_check(first_job, j) && !job_is_completed(j) &&
													!job_is_stopped(j))
		{
			j->execution = 1;
			launch_job(j, j->separator == T_AND ? 0 : 1);
		}
		else
			j->execution = 0;
		j = j->next;
	}
}
