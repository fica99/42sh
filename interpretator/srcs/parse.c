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

int		simp_command(t_lex_tkn **list)
{
	t_process	*curr_proc;

	if ((*list)->type == T_END)
		return (0);
	curr_proc = add_process(g_first_job);
	if (!(list = parse_ass_words(list, curr_proc)))
		return (0);
	return (word_list(list, curr_proc));
}

int		pipe_sequence(t_lex_tkn **list)
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

int		start(t_lex_tkn **list)
{
	t_lex_tkn	**tmp;
	t_job		*new;

	if ((*list)->type == T_END)
		return (0);
	else if ((*list)->class == C_SEP)
		return (syntax_err(*list));
	tmp = find_token(list, C_SEP);
	new = job_new();
	if ((*tmp)->type != T_END)
		new->separator = (*tmp)->type;
	if (new->separator == T_AND)
		new->foreground = 0;
	tmp = split_list(tmp);
	if ((pipe_sequence(list)) < 0)
		return (-1);
	return (start(tmp));
}

void	ft_sub(t_lex_tkn **list)
{
	while ((*list)->type != T_END)
	{
		if ((*list)->type == T_WORD)
		{
			if (ft_strchr((*list)->value, '"'))
				ft_strccut((*list)->value, '"');
			if (ft_strchr((*list)->value, '\''))
				ft_strccut((*list)->value, '\'');
			(*list)->value = spec_symbols((*list)->value);
		}
		list++;
	}
}

void	parse(t_lex_tkn **tokens)
{
	if (!tokens)
		return ;
	if (!*tokens || (*tokens)->type == T_END)
	{
		lex_del_tkns(tokens);
		return ;
	}
	ft_sub(tokens);
	if (!start(tokens))
		exec_jobs(g_first_job);
	ft_free_jobs(g_first_job);
	g_first_job = 0;
	lex_del_tkns(tokens);
}
