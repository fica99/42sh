/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:13:47 by ggrimes           #+#    #+#             */
/*   Updated: 2019/10/18 19:45:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_shell.h"

int			lx_init_tokens(t_tokens *tokens, t_string *str, t_lexer *lexer)
{
	tokens->previous = NULL;
	if (!(tokens->current = lx_get_token(str, lexer)))
		return (0);
	tokens->current = lx_skip(tokens->current, str, lexer);
	tokens->next = NULL;
	tokens->union_pc = 0;
	tokens->union_cn = 0;
	tokens->priority_pc = 0;
	tokens->priority_cn = 0;
	tokens->error_msg = NULL;
	return (1);
}

int			lx_init_next_token(t_tokens *tokens, t_string *str, t_lexer *lexer)
{
	if (!(tokens->next = lx_get_token(str, lexer)))
		return (0);
	return (1);
}

t_token		*lx_skip(t_token *token, t_string *str, t_lexer *lexer)
{
	while (token->class == LEXER_SKIP_CLASS)
	{
		lx_clear_token(&token);
		if (!(token = lx_get_token(str, lexer)))
			return (NULL);
	}
	return (token);
}
