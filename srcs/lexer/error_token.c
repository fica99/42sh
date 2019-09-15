/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:26:49 by ggrimes           #+#    #+#             */
/*   Updated: 2019/09/15 22:48:47 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_token		*class_error(t_token *token, t_token *next_token)
{
	if (token)
		clear_token(&token);
	if(next_token)
		clear_token(&next_token);
	return token_error();
}

t_token		*token_error(void)
{
	t_token	*token;

	if (!(token = new_token()))
		return (NULL);
	token->type = FT_ERROR;
	token->class = C_FT_ERROR;
	return (token);
}

t_token		*eof_token(void)
{
	t_token	*token;

	if (!(token = new_token()))
		return (NULL);
	token->type = EOL;
	token->class = C_SEP;
	return (token);
}

int			tokens_error(t_tokens *tokens, t_string *str)
{
	t_token	*token;

	if (tokens->previous)
		clear_token(&(tokens->previous));
	if (tokens->current)
		clear_token(&(tokens->current));
	if (tokens->next)
		clear_token(&(tokens->next));
	while ((token = (t_token *)ft_fifo(1, "get", NULL)))
	{
		clear_token(&token);
	}
	str->index = 0;
	return (-2);
}