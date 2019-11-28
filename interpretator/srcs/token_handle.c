/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:50:39 by mmarti            #+#    #+#             */
/*   Updated: 2019/11/28 07:50:40 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

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

t_token *get_next_grammar(t_token *token)
{
	t_token *tmp;

	if (!token)
		return (NULL);
	tmp = token->next;
	rmtoken(token);
	return (tmp);
}
