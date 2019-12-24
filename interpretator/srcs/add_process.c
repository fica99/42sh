/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:18:31 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/21 13:18:33 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_job		*get_last_job(void)
{
	t_job *tmp;

	tmp = g_first_job;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_process	*get_last_proc(t_job *job)
{
	t_process *tmp;

	tmp = job->first_process;
	if (!tmp)
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_process	*proc_new(void)
{
	t_process *new;

	if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	new->args_size = DEF_ARGS_SIZE;
	new->redir_size = DEF_REDIR_SIZE;
	if (!(new->fd_list = (int **)ft_memalloc(sizeof(int *) * DEF_REDIR_SIZE)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	if (!(new->args = (char **)ft_memalloc(sizeof(char *) * DEF_ARGS_SIZE)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	new->inpipe = STDIN_FILENO;
	new->outpipe = STDOUT_FILENO;
	return (new);
}

t_process	*add_process(t_job *first_job)
{
	t_process	*proc;
	t_process	*tmp;

	proc = proc_new();
	while (first_job->next)
		first_job = first_job->next;
	tmp = first_job->first_process;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	if (!tmp)
		first_job->first_process = proc;
	else
		tmp->next = proc;
	return (proc);
}

t_job		*job_new(void)
{
	t_job *new;
	t_job *tmp;

	if (!(new = (t_job *)ft_memalloc(sizeof(t_job))))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	new->pgid = getpgrp();
	new->tmodes = &g_shell_tmodes;
	if (!g_first_job)
		g_first_job = new;
	else
	{
		tmp = g_first_job;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}
