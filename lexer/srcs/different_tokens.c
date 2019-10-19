/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   different_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:27:23 by ggrimes           #+#    #+#             */
/*   Updated: 2019/10/19 18:14:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int			lx_different_tokens(t_tokens *tokens, t_string *str)
{
	if (tokens->priority_pc >= tokens->priority_cn)
		return (lx_left_priority(tokens, str));
	return (lx_right_priority(tokens, str));
}

int			lx_left_priority(t_tokens *tokens, t_string *str)
{
	if (tokens->previous)
	{
		tokens->previous->type = tokens->union_pc;
		ft_fifo(1, "add", (void *)(tokens->previous));
	}
	tokens->current->type = tokens->union_pc;
	ft_fifo(1, "add", (void *)(tokens->current));
	str->index = tokens->next->start_index;
	lx_clear_token(&(tokens->next));
	return (0);
}

int			lx_right_priority(t_tokens *tokens, t_string *str)
{
	if (tokens->previous)
		ft_fifo(1, "add", (void *)(tokens->previous));
	str->index = tokens->current->start_index;
	lx_clear_token(&(tokens->current));
	lx_clear_token(&(tokens->next));
	return (0);
}
