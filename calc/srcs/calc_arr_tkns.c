/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_arr_tkns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 14:50:52 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/05 19:53:59 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

static t_calc_tkns	*calc_new_tkns(void)
{
	t_calc_tkns		*s_tokens;
	t_calc_tkn		*tokens;

	if (!(s_tokens = (t_calc_tkns *)malloc(sizeof(t_calc_tkns))))
		return (NULL);
	if (!(tokens = (t_calc_tkn *)malloc(sizeof(t_calc_tkn) * (CALC_TOKENS_SIZE))))
	{
		free(s_tokens);
		return (NULL);
	}
	s_tokens->tokens = tokens;
	s_tokens->malloc_size = CALC_TOKENS_SIZE;
	s_tokens->size = 0;
	return (s_tokens);
}

static t_calc_tkns	*calc_reloc_tkns(t_calc_tkns *s_tokens)
{
	t_calc_tkn		*new_tokens;

	if (!s_tokens)
		return (NULL);
	if (!(new_tokens = (t_calc_tkn *)malloc(sizeof(t_calc_tkn) * (s_tokens->malloc_size + CALC_TOKENS_SIZE))))
		return s_tokens;
	new_tokens = ft_memcpy(new_tokens, s_tokens->tokens, sizeof(t_calc_tkn) * s_tokens->malloc_size);
	free(s_tokens->tokens);
	s_tokens->tokens = new_tokens;
	s_tokens->malloc_size += CALC_TOKENS_SIZE;
	return (s_tokens);
}

t_calc_tkns			*calc_get_arr_tkns(char *str)
{
	t_calc_tkns 	*s_tokens;
	t_calc_tkn		*token;
	size_t			pos;

	if (!str)
		return (NULL);
	pos = 0;
	if (!(s_tokens = calc_new_tkns()))
		return (NULL);
	while (1)
	{
		if (!(token = calc_get_next_tkn(str, pos)))
			return (calc_del_tkns(s_tokens));
		ft_memcpy(&s_tokens->tokens[s_tokens->size], token, sizeof(t_calc_tkn));
		s_tokens->size++;
		pos = token->end_pos;
		free(token);
		if (s_tokens->tokens[s_tokens->size - 1].type == CALC_END)
			break;
		if (s_tokens->size == s_tokens->malloc_size)
			s_tokens = calc_reloc_tkns(s_tokens);
	}
	return (s_tokens);
}

t_calc_tkns 		*calc_del_tkns(t_calc_tkns *s_tokens)
{
	size_t			i;

	if (!s_tokens)
		return (NULL);
	i = -1;
	while (++i < s_tokens->size)
		if (s_tokens->tokens[i].value)
			free(s_tokens->tokens[i].value);
	free(s_tokens->tokens);
	free(s_tokens);
	return (NULL);
}

int					calc_check_index(t_calc_tkns *s_tokens, size_t index)
{
	if (!s_tokens)
		return (0);
	if (index < s_tokens->size)
		return (1);
	return (0);
}
