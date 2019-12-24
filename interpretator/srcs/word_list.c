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
			if (!(tmp = ft_realloc(curr_proc->args,
			curr_proc->args_size / 2 * sizeof(char *), curr_proc->args_size * sizeof(char *))))
				err_exit("42sh", "malloc() error", NULL, NOERROR);
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

t_lex_tkn	**check_valid_ass_word(t_lex_tkn **list)
{
	t_lex_tkn **tmp;

	tmp = list;
	while ((*list)->type != T_END)
	{
		if ((*list)->type != T_ASSIGNMENT_WORD)
			return (list);
		list++;
	}
	return (tmp);
}

t_lex_tkn	**parse_ass_words(t_lex_tkn **list, t_process *curr_proc)
{
	size_t	i;

	i = 1;
	list = check_valid_ass_word(list);
	if ((*list)->type != T_ASSIGNMENT_WORD)
		return (list);
	curr_proc->args[0] = ft_strdup("set_var");
	while ((*list)->type != T_END)
	{
		if (!(curr_proc->args[i++] = ft_strdup((*list)->value)))
			err_exit("42sh", "malloc() error", NULL, NOERROR);
		if (i >= curr_proc->args_size - 2)
		{
			curr_proc->args_size *= 2;
			if (!(curr_proc->args = ft_realloc(curr_proc->args,
			curr_proc->args_size / 2 * sizeof(char *), curr_proc->args_size * sizeof(char *))))
				err_exit("42sh", "malloc() error", NULL, NOERROR);
		}
		list++;
	}
	return (NULL);
}

int			word_list(t_lex_tkn **list, t_process *cur_proc)
{
	if ((*list)->type == T_END)
		return (0);
	else if ((*list)->type == T_IO_NUMBER || (*list)->class == C_REDIR)
		return (parse_redirect(list, cur_proc));
	else if ((*list)->type == T_WORD)
		return (parse_word(list, cur_proc));
	else
		return (syntax_err(*list));
}
