/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tkns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:45:36 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/12 22:03:35 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkns	*lex_new_tkns(void)
{
	t_lex_tkns	*s_tokens;
	t_lex_tkn	**new_tkns;

	if (!(s_tokens = (t_lex_tkns *)malloc(sizeof(t_lex_tkns))))
		return (NULL);
	if (!(new_tkns = (t_lex_tkn **)malloc(sizeof(t_lex_tkn *)
		* (LEX_TOKENS_SIZE + 1))))
	{
		ft_memdel((void **)s_tokens);
		return (NULL);
	}
	new_tkns[0] = NULL;
	s_tokens->tokens = new_tkns;
	s_tokens->malloc_size = LEX_TOKENS_SIZE;
	s_tokens->size = 0;
	return (s_tokens);
}

t_lex_tkns	*lex_tkns_reloc(t_lex_tkns *s_tokens)
{
	t_lex_tkn	**reloc_tokens;
	size_t		malloc_size;

	if (!s_tokens)
		return (NULL);
	malloc_size = s_tokens->malloc_size + LEX_TOKENS_SIZE;
	if (!(reloc_tokens = (t_lex_tkn **)malloc(sizeof(t_lex_tkn *)
		* (malloc_size + 1))))
		return (s_tokens);
	reloc_tokens[s_tokens->size] = NULL;
	reloc_tokens = ft_memcpy(reloc_tokens, s_tokens->tokens,
		sizeof(t_lex_tkn *) * (s_tokens->size));
	free(s_tokens->tokens);
	s_tokens->tokens = reloc_tokens;
	s_tokens->malloc_size = malloc_size;
	return (s_tokens);
}

t_lex_tkn	**lex_del_tkns(t_lex_tkn **tokens)
{
	size_t		i;

	if (!tokens)
		return (NULL);
	i = 0;
	while (tokens[i])
		lex_del_tkn(tokens[i++]);
	free(tokens);
	return (NULL);
}

t_lex_tkn	**lex_del_s_tokens(t_lex_tkns *s_tokens)
{
	if (!s_tokens)
		return (NULL);
	lex_del_tkns(s_tokens->tokens);
	free(s_tokens);
	return (NULL);
}
