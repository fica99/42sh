/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:26:49 by ggrimes           #+#    #+#             */
/*   Updated: 2019/09/18 20:13:44 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_token		*lx_class_error(t_token *token, t_token *next_token,
	char *msg, t_string *str)
{
	if (token)
		lx_clear_token(&token);
	if (next_token)
		lx_clear_token(&next_token);
	return (lx_token_error(msg, str));
}

t_token		*lx_token_error(char *msg, t_string *str)
{
	t_token	*token;

	if (!(token = new_token()))
		return (NULL);
	token->type = FT_ERROR;
	token->class = C_FT_ERROR;
	if (msg)
		if (!(token->lexeme = ft_strdup(msg)))
			return (NULL);
	str->index = 0;
	return (token);
}

t_token		*lx_eof_token(void)
{
	t_token	*token;

	if (!(token = new_token()))
		return (NULL);
	token->type = EOL;
	token->class = C_SEP;
	return (token);
}

int			lx_tokens_error(t_tokens *tokens, t_string *str)
{
	t_token	*token;

	if (tokens->previous)
		lx_clear_token(&(tokens->previous));
	if (tokens->current)
		lx_clear_token(&(tokens->current));
	lx_put_error(tokens, tokens->next->lexeme);
	if (tokens->next)
		lx_clear_token(&(tokens->next));
	while ((token = (t_token *)ft_fifo(1, "get", NULL)))
		lx_clear_token(&token);
	str->index = 0;
	return (-2);
}

int			lx_put_error(t_tokens *tokens, char *msg)
{
	if (tokens->error_msg)
	{
		free(tokens->error_msg);
		tokens->error_msg = NULL;
	}
	if (msg)
		tokens->error_msg = ft_strdup(msg);
	return (-2);
}
