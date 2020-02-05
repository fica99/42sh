/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:18:31 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/05 14:16:33 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int					max_job(void)
{
	t_job	*j;
	int		max;

	max = 0;
	j = g_first_job;
	while (j)
	{
		if (j->num > max)
			max = j->num;
		j = j->next;
	}
	return (max + 1);
}

static t_process	*proc_new(void)
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

t_process			*add_process(t_job *j)
{
	t_process	*proc;
	t_process	*tmp;

	proc = proc_new();
	tmp = j->first_process;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	if (!tmp)
		j->first_process = proc;
	else
		tmp->next = proc;
	return (proc);
}

t_job				*job_new(t_lex_tkn **sep)
{
	t_job	*new;
	t_job	*tmp;

	if (!(new = (t_job *)ft_memalloc(sizeof(t_job))))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	new->pgid = 0;
	new->tmodes = &g_shell_tmodes;
	if (sep)
		new->separator = (*sep)->type;
	if (!g_first_job)
		g_first_job = new;
	else
	{
		tmp = g_first_job;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	new->num = max_job();
	return (new);
}
