/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:50:57 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/21 13:50:58 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	parse_word(t_lex_tkn **list, t_process *curr_proc)
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
			if (!(tmp = ft_realloc(curr_proc->args, curr_proc->args_size / 2,
			curr_proc->args_size)))
				err_exit("42sh", "malloc() error", NULL, NOERROR);
			ft_free_dar(curr_proc->args);
			curr_proc->args = tmp;
		}
		i++;
	}
	tmp[i] = ft_strdup((*list)->value);
	return (word_list(++list, curr_proc));
}

static int	parse_redirect(t_lex_tkn **list, t_process *curr_proc)
{
	int						io_number;
	static	t_redirect_func	red[6] = {&g_redir, &g_redir, &l_redir,
	&here_doc, &l_aggr, &g_aggr};

	io_number = -1;
	if ((*list)->type == T_IO_NUMBER)
	{
		io_number = *(*list)->value - 48;
		list++;
	}
	if ((*(list + 1))->type != T_WORD)
		return (syntax_err(*(list + 1)));
	return (red[(*list)->type - 6](list, curr_proc, io_number));
}

static int	parse_assignment_word(t_lex_tkn **list, t_process *curr_proc)
{
	char *name;
	char *value;

	name = (*list)->value;
	list += 2;
	value = (*list)->value;
	set_env(name, value, SET_ENV);
	return (word_list(++list, curr_proc));
}

int			word_list(t_lex_tkn **list, t_process *cur_proc)
{
	if ((*list)->type == T_END)
		return (0);
	else if ((*list)->type == T_IO_NUMBER || (*list)->class == C_REDIR)
		return (parse_redirect(list, cur_proc));
	else if ((*list)->type == T_WORD)
		return (parse_word(list, cur_proc));
	else if ((*list)->type == T_ASSIGNMENT_WORD)
		return (parse_assignment_word(list, cur_proc));
	else
		return (syntax_err(*list));
}
