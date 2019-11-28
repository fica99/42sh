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

int syntax_err(t_token *token)
{
	ft_putstr("42sh: ");
	ft_putstr("syntax error near unexpected token: ");
	ft_putstr(token->lexeme);
	return (-1);
}

void	add_logical(t_token *token)
{
	//todo
}

t_job *job_new(void)
{
	t_job *new;
	t_job *tmp;

	if (!(new = (t_job *)ft_memalloc(sizeof(t_job))))
		err_exit(g_argv[0], "malloc() error", NULL, NOERROR);
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

t_token *find_token(t_token *list, int type)
{
	//todo
	return (NULL);
}

void	rmtoken(t_token *token)
{
	if (!token)
		return ;
	//todo
}



int	logical_list(t_token *list)
{
	t_token *logical;
	t_token *tmp;

	if (!list)
		return (0);
	if (tk_class(list, LOGICAL))
		return (syntax_err(list));
	tmp = NULL;
	logical = find_token(list, LOGICAL);
	add_logical(list);
	if (logical)
		tmp = logical->next;
	rmtoken(logical);
	if ((pipeline(list)) < 0)
		return (-1);
	return (logical_list(tmp));
}

int	start(t_token *list)
{
	t_token *semi;
	t_token	*tmp;

	if (!list)
		return (0);
	if (tk_class(list, SEMI))
		return (syntax_err(list));
	tmp = NULL;
	if ((semi = find_token(list, SEMI)))
		tmp = semi->next;
	rmtoken(semi);
	if ((logical_list(list)) < 0)
		return (-1);
	return (start(tmp));
}

void	interpret_ast(t_token *list)
{
	t_job *jobs_list;

	if (!list)
		return ;
	start(list);
}
