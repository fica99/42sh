/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:25:50 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/17 22:43:47 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static t_lex_tkn	**re_tkns(t_lex_tkns *s_tokens)
{
	t_lex_tkn	**tokens;

	if (!s_tokens)
		return (NULL);
	tokens = s_tokens->tokens;
	free(s_tokens);
	return (tokens);
}

t_lex_tkn			**lex_get_tkns(char **str)
{
	t_lex_tkns	*s_tokens;
	t_lex_tkn	*token;
	size_t		pos;

	if (!str || !(*str))
		return (NULL);
	if (!(s_tokens = lex_new_tkns()))
		return (NULL);
	pos = 0;
	while (1)
	{
		if (!(token = lex_get_next_tkn(str, pos)))
			return (lex_del_s_tokens(s_tokens));
		pos = token->end_pos;
		s_tokens->tokens[s_tokens->size] = token;
		s_tokens->size++;
		s_tokens->tokens[s_tokens->size] = NULL;
		if (token->type == T_END)
			break ;
		if (s_tokens->size == s_tokens->malloc_size)
			s_tokens = lex_tkns_reloc(s_tokens);
	}
	return (re_tkns(s_tokens));
}
