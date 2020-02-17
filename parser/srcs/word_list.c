/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:50:57 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/12 18:20:42 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	parse_word(t_lex_tkn **list, t_process *curr_proc)
{
	size_t	i;
	char	**tmp;

	i = 0;
	tmp = curr_proc->args;
	while (tmp[i])
	{
		if (i >= curr_proc->args_size - 2)
		{
			curr_proc->args_size *= 2;
			if (!(tmp = ft_realloc(curr_proc->args, curr_proc->args_size / 2
			* sizeof(char *), curr_proc->args_size * sizeof(char *))))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
			curr_proc->args = tmp;
		}
		i++;
	}
	tmp[i] = ft_strdup((*list)->value);
	return (word_list(++list, curr_proc));
}

static void	parse_redirect(t_lex_tkn **list, t_process *curr_proc)
{
	t_redir_list	*new;
	t_redir_list	*first_red;
	int				exp_w;

	exp_w = (*(list))->type == T_IO_NUMBER ? 3 : 2;
	first_red = curr_proc->r;
	if (!(new = (t_redir_list *)ft_memalloc(sizeof(t_redir_list))))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	new->rd_token = list;
	if (!first_red)
		curr_proc->r = new;
	else
	{
		while (first_red->next)
			first_red = first_red->next;
		first_red->next = new;
	}
	if (!*curr_proc->args && (*(list + exp_w))->class == C_END)
		exp_w = 1;
	return (word_list(list + exp_w, curr_proc));
}

static void	add_set_var_proc(char **varlist,
t_process *p, t_lex_tkn **list)
{
	int ac;
	int i;

	i = 0;
	ac = ft_darlen(varlist) + 1;
	if (ac >= DEF_ARGS_SIZE)
	{
		free(p->args);
		if (!(p->args = ft_memalloc(sizeof(char *) * (ac + 1))))
			err_exit("42sh", "malloc() error", NULL, NOERROR);
	}
	p->args[0] = ft_strdup("set_var");
	while (varlist[i])
	{
		p->args[i + 1] = varlist[i];
		i++;
	}
	free(varlist);
	return (word_list(list, p));
}

void		h_ass_words(t_lex_tkn **list, t_process *p)
{
	t_ass_vars v;

	v.size = DEF_VARLIST_SIZE;
	v.i = 0;
	if (!(v.varlist = (char **)ft_memalloc(sizeof(char *) * v.size)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	while ((*list)->type == T_ASSIGNMENT_WORD)
	{
		if (!(v.varlist[v.i] = ft_strdup((*list)->value)))
			err_exit("42sh", "malloc() error", NULL, NOERROR);
		if (v.i >= v.size - 2)
		{
			v.size *= 2;
			if (!(v.varlist = ft_realloc(v.varlist,
			v.size / 2 * sizeof(char *), v.size * sizeof(char *))))
				err_exit("42sh", "malloc() error", NULL, NOERROR);
		}
		list++;
		v.i++;
	}
	if ((*list)->type == T_WORD)
		p->environment = v.varlist;
	else
		return (add_set_var_proc(v.varlist, p, list));
	return (word_list(list, p));
}

void		word_list(t_lex_tkn **list, t_process *cur_proc)
{
	if ((*list)->type == T_IO_NUMBER || (*list)->class == C_REDIR)
		parse_redirect(list, cur_proc);
	else if ((*list)->class == C_WORD)
		parse_word(list, cur_proc);
}
