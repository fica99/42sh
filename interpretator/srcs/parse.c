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
	if (!(new->redir = (int **)ft_memalloc(sizeof(int *) * 16)))
		err_exit(g_argv[0], "malloc() error", NULL, NOERROR);
	return (new);
}

t_process	*add_process(t_token *token)
{
	t_process	*proc;
	t_process	*tmp;
	t_job		*last_job;

	proc = proc_new();
	if (token)
	{
		last_job = get_last_job();
		tmp = get_last_proc(last_job);
		if (!tmp)
			last_job->first_process = proc;
		else
			tmp->next = proc;
		proc->args = ft_strtok(token->lexeme);
	}
    return (proc);
}

void	add_redir(t_process *proc, int *fd)
{
	int **tmp = proc->redir;

	while (*tmp)
		tmp++;
	*tmp = fd;
}

int ft_open(t_token *file, int flag)
{
	int fd;

	if (file->type != WORD)
		return (syntax_err(file));
	if ((fd = open(file->lexeme, flag)) < 0)
		return (-1);
	return (fd);
}

int g_redir(t_token *redir, t_process *curr_proc)
{
	int *fd;

	if (!(fd = (int *)malloc(sizeof(int))))
		err_exit(g_argv[0], "malloc() error", NULL, NOERROR);
	fd[1] = 1;
	if (*(redir->lexeme) != '>')
		fd[1] = ft_atoi(redir->lexeme);
	if ((fd[0] = ft_open(redir + 1, RRED_OPEN)) < 0)
	{
		free(fd);
		return (-1);
	}
	add_redir(curr_proc, fd);
	free(redir++);
	free(redir++);
	return (redirect_list(redir, curr_proc));
}

int dg_redir(t_token *redir, t_process *curr_proc)
{
	int *fd;

	if (!(fd = (int *)malloc(sizeof(int))))
		err_exit(g_argv[0], "malloc() error", NULL, NOERROR);
	fd[1] = 1;
	if (*(redir->lexeme) != '>')
		fd[1] = ft_atoi(redir->lexeme);
	if ((fd[0] = ft_open(redir + 1, DRRED_OPEN)) < 0)
	{
		free(fd);
		return (-1);
	}
	add_redir(curr_proc, fd);
	free(redir++);
	free(redir++);
	return (redirect_list(redir, curr_proc));
}

int l_redir(t_token *redir, t_process *curr_proc)
{
	int *fd;

	if (!(fd = (int *)malloc(sizeof(int))))
		err_exit(g_argv[0], "malloc() error", NULL, NOERROR);
	fd[0] = 0;
	if (*(redir->lexeme) != '>')
		fd[0] = ft_atoi(redir->lexeme);
	if ((fd[1] = ft_open(redir + 1, LRED_OPEN)) < 0)
	{
		free(fd);
		return (-1);
	}
	add_redir(curr_proc, fd);
	free(redir++);
	free(redir++);
	return (redirect_list(redir, curr_proc));
}

int here_doc()

int redirect_list(t_token *redir, t_process *cur_proc)
{
    if (!redir)
        return (0);
	else if (!tk_class(redir, REDIR))
        return (-1);
    else if (redir->type == GREAT)
		return (g_redir(redir, cur_proc));
	else if (redir->type == DGREAT)
		return (dg_redir(redir, cur_proc));
	else if (redir->type == LESS)
		return (l_redir(redir, cur_proc));
	else if (redir->type == DLESS)
		return (here_doc(redir, cur_proc));
	//todo
}

int simp_command(t_token *list)
{
	t_token *tmp;
    t_process *curr_proc;

	if (!list)
		return (0);
	curr_proc = add_process(find_token(list, WORD));
	if ((tmp = find_token(list, REDIR)))
        return (redirect_list(tmp, curr_proc));
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
	if ((simp_command(list) < 0))
		return (-1);
	return (pipe_sequence(tmp));
}

int	logical_list(t_token *list)
{
	t_token *tmp;

	if (!list)
		return (0);
	if (tk_class(list, LOGICAL))
		return (syntax_err(list));
	tmp = find_token(list, LOGICAL);
	add_logical(tmp);
	tmp = split_list(tmp);
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
