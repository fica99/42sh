/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:51:16 by mmarti            #+#    #+#             */
/*   Updated: 2019/11/28 07:51:17 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_sep_list	*new_sep_list(t_token *token)
{
	t_sep_list *new;

	if (!(new = (t_sep_list *)ft_memalloc(sizeof(t_sep_list))))
		err_exit(g_argv[0], "malloc() error", NULL, NOERROR);
	new->sep = token->type;
	return (new);
}

void	add_logical(t_token *token)
{
	t_sep_list *tmp;

	if (!token)
		return ;
	if (!g_sep_list)
		g_sep_list = new_sep_list(token);
	else
	{
		tmp = g_sep_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_sep_list(token);
	}
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
