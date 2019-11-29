/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:55:45 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/19 18:14:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_job *get_last_job()
{
	t_job *tmp;

	tmp = g_first_job;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_process *get_last_proc(t_job *job)
{
	t_process *tmp;

	tmp = job->first_process;
	if (!tmp)
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_process *proc_new()
{
	t_process *new;

	if (!(new = (t_process *)ft_memalloc(sizeof(new))))
		err_exit(g_argv[0], "malloc() error", NULL, NOERROR);
	return (new);
}

void	add_process(t_token *token)
{
	t_process	*proc;
	t_process	*tmp;
	t_job		*last_job;

	proc = proc_new();
	last_job = get_last_job();
	tmp = get_last_proc(last_job);
	if (!tmp)
		last_job->first_process = proc;
	else
		tmp->next = proc;
	proc->args = ft_strtok(token->lexeme);
}

int commamd(t_token *list)
{
	t_token *tmp;

	if (!list)
		return (0);
	if (list->type != WORD)
		return (-1);
	add_process(list);
	return (0);
}

int	pipe_sequence(t_token *list)
{
	t_token *tmp;

	if (!list)
		return (0);
	if (tk_type(list, PIPE))
		return (syntax_err(list));
	tmp = split_list(find_token(list, PIPE));
	if ((command(list) < 0))
		return (-1);
	return (pipe_sequence(tmp));
}

int	logical_list(t_token *list)
{
	t_token *logical;
	t_token *tmp;

	if (!list)
		return (0);
	if (tk_class(list, LOGICAL))
		return (syntax_err(list));
	logical = find_token(list, LOGICAL);
	add_logical(list);
	tmp = split_list(logical);
	if ((pipe_sequence(list)) < 0)
		return (-1);
	return (logical_list(tmp));
}

int	start(t_token *list)
{
	t_token	*tmp;

	if (!list)
		return (0);
	if (tk_class(list, SEMI))
		return (syntax_err(list));
	tmp = split_list(find_token(list, tk_class(SEMI)))
	if ((logical_list(list)) < 0)
		return (-1);
	return (start(tmp));
}

void	parse(t_token *list)
{
	t_job *jobs_list;

	if (!list)
		return ;
	start(list);
}
