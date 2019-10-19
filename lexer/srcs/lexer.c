/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:29:32 by ggrimes           #+#    #+#             */
/*   Updated: 2019/10/19 18:14:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_token		*get_next_token(t_string *str, t_lexer *lexer)
{
	t_tokens	tokens;
	int			state;

	if (!lx_init_tokens(&tokens, str, lexer))
		return (NULL);
	if (tokens.current->type == EOL || tokens.current->type == FT_ERROR)
		return (tokens.current);
	while (1)
	{
		if (!(lx_init_next_token(&tokens, str, lexer)))
			return (NULL);
		state = lx_check_tokens(&tokens, lexer, str);
		if (state == -2)
			return (lx_token_error(tokens.error_msg, str));
		if (state == 0)
			break ;
	}
	return (lx_get_union_token(lexer, str));
}

int			lx_no_previous(t_tokens *tokens, t_string *str, t_lexer *lexer)
{
	tokens->union_cn = lx_define_union(tokens->current, tokens->next, lexer);
	tokens->union_pc = tokens->union_cn;
	if (tokens->union_cn == -2)
		return (lx_tokens_error(tokens, str));
	else if (tokens->union_cn == 0)
		return (lx_completed_token(tokens, str));
	else if (tokens->union_cn == -3)
		return (lx_miss_token(tokens, str));
	else
		return (lx_equal_tokens(tokens, str));
}

int			lx_get_union_params(t_tokens *tokens, t_lexer *lexer)
{
	if ((tokens->union_cn = lx_define_union(tokens->current,
		tokens->next, lexer)) == -2)
		return (0);
	if (tokens->previous)
	{
		if ((tokens->union_pc = lx_define_union(tokens->previous,
			tokens->current, lexer)) == -2)
			return (0);
	}
	else
		tokens->union_pc = tokens->union_cn;
	return (1);
}

int			lx_get_priority_params(t_tokens *tokens, t_lexer *lexer)
{
	if ((tokens->priority_cn = lx_define_priority(tokens->current,
		tokens->next, lexer)) == -2)
		return (0);
	if (tokens->previous)
	{
		if ((tokens->priority_pc = lx_define_priority(tokens->previous,
			tokens->current, lexer)) == -2)
			return (0);
	}
	else
		tokens->priority_pc = tokens->priority_cn;
	return (1);
}

void		lx_clear_token(t_token **token)
{
	if (!*token)
		return ;
	if ((*token)->lexeme)
		free((*token)->lexeme);
	free(*token);
	*token = NULL;
}
