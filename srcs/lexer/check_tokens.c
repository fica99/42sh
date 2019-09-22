/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:04:08 by ggrimes           #+#    #+#             */
/*   Updated: 2019/09/19 22:29:21 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int			lx_check_tokens(t_tokens *tokens, t_lexer *lexer, t_string *str)
{
	if (!tokens->previous)
		return (lx_no_previous(tokens, str, lexer));
	if (!lx_get_union_params(tokens, lexer))
		return (lx_put_error(tokens, "Define union"));
	if (!lx_get_priority_params(tokens, lexer))
		return (lx_put_error(tokens, "Define priority"));
	if (tokens->union_pc != tokens->union_cn)
	{
		if (tokens->union_cn == -2)
			return (lx_tokens_error(tokens, str));
		else if (tokens->union_cn == 0)
			return (lx_completed_token(tokens, str));
		else if (tokens->union_cn == -3)
			return (lx_miss_token(tokens, str));
		else
			return (lx_different_tokens(tokens, str));
	}
	else
		return (lx_equal_tokens(tokens, str));
}

int			lx_miss_token(t_tokens *tokens, t_string *str)
{
	if (tokens->next)
	{
		str->index = tokens->next->fin_index;
		lx_clear_token(&tokens->next);
	}
	return (1);
}

int			lx_completed_token(t_tokens *tokens, t_string *str)
{
	if (tokens->previous)
	{
		tokens->previous->type = tokens->union_pc;
		ft_fifo(1, "add", (void *)(tokens->previous));
		tokens->current->type = tokens->union_pc;
	}
	ft_fifo(1, "add", (void *)(tokens->current));
	str->index = tokens->next->start_index;
	lx_clear_token(&(tokens->next));
	return (0);
}

int			lx_equal_tokens(t_tokens *tokens, t_string *str)
{
	if (tokens->previous)
	{
		tokens->previous->type = tokens->union_pc;
		ft_fifo(1, "add", (void *)(tokens->previous));
	}
	tokens->previous = tokens->current;
	tokens->current = tokens->next;
	tokens->next = NULL;
	str->index = tokens->current->fin_index;
	return (tokens->union_pc);
}
