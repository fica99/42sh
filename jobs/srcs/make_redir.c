/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 00:54:51 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/25 16:31:33 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	make_redir(t_lex_tkn **list, t_process *curr_proc)
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
	return (red[(*list)->type - 7](list, curr_proc, io_number));
}

void		dup_redir(int **fd_list)
{
	while (*fd_list)
	{
		if ((*fd_list)[0] == -1)
			close((*fd_list)[1]);
		dup2((*fd_list)[0], (*fd_list)[1]);
		fd_list++;
	}
}

int			redir_handle(t_process *p)
{
	t_redir_list *tmp;

	tmp = p->r;
	while (tmp)
	{
		if (make_redir(tmp->rd_token, p) < 0)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
