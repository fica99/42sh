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

int simp_command(t_lex_tkn **list)
{
    t_process *curr_proc;

	if ((*list)->type == T_END)
		return (0);
	curr_proc = add_process();
    return (redirect_list(list, curr_proc));
}

int	pipe_sequence(t_lex_tkn **list)
{
	t_lex_tkn **tmp;

	if ((*list)->type == T_END)
		return (0);
	if ((*list)->class == C_PIPE)
		return (syntax_err(*list));
	tmp = split_list(find_token(list, C_PIPE));
	if ((simp_command(list) < 0))
		return (-1);
	return (pipe_sequence(tmp));
}

int	logical_list(t_lex_tkn **list)
{
	// t_lex_tkn **tmp;

	// if (!*list)
	// 	return (0);
	// if ((*list)->class == C_LOGICAL)
	// 	return (syntax_err(list));
	// tmp = find_token(list, LOGICAL);
	// add_logical(tmp);
	// tmp = split_list(tmp);
	
	if ((pipe_sequence(list)) < 0)
		return (-1);
	return (0);
	// return (logical_list(tmp));
}

void	rmjob_last_job(t_job **j)
{
	if (!*j)
		return ;
	while ((*j)->next)
		j = &(*j)->next;
    ft_free_proc((*j)->first_process);
    if ((*j)->command)
        free((*j)->command);
    free(*j);
	*j = NULL;
}

int	start(t_lex_tkn **list)
{
	t_lex_tkn **tmp;

	if ((*list)->type == T_END)
		return (0);
	tmp = split_list(find_token(list, C_SEP));
	if ((*list)->type != T_END)
		job_new();
	if ((logical_list(list)) < 0)
		rmjob_last_job(&g_first_job);
	return (start(tmp));
}

void print_proc(t_job *job)
{
	t_process *proc = job->first_process;

	while (proc && proc->args)
	{
		printf("*********************\n");
		while (*proc->args)
		{
			printf("%s\n", *proc->args);
			proc->args++;
		}
		while (*proc->redir)
		{
			printf("%d <== %d\n", (*proc->redir)[0], (*proc->redir)[1]);
			proc->redir++;
		}
		printf("*********************\n");
		proc = proc->next;
	}
}

void print_jobs(t_job *first_job)
{
	int i = 0;

	while (first_job)
	{
		printf("job %i\n", i);
		print_proc(first_job);
		first_job = first_job->next;
		i++;
	}
}

int	get_token_ind(t_lex_tkn **token_list, t_lex_tkn *token)
{
	int i;

	i = 0;
	if (!token)
		return (-1);
	while (token_list[i] != token)
		i++;
	return(i);
}

void	parse(t_lex_tkn **tokens)
{
	if (!*tokens || (*tokens)->type == T_END)
		return ;
	// lex_print_tkns(tokens);
	// return;
	if (start(tokens) == 0 && g_first_job)
		launch_job(g_first_job, 0);
	//close_fds(g_first_job);
	lex_del_tkns(tokens);
	//print_jobs(g_first_job);
	ft_free_jobs(g_first_job);
	g_first_job = 0;
}
