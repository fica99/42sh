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

int	pipe_sequence(t_token *list)
{
	if (!list)
		return (0);
	if (tk_type(list, PIPE))
		return (syntax_err(list));

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
	tmp = get_next_grammar(logical);
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
	tmp = get_next_grammar(find_token(list, tk_class(SEMI)))
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
