/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_arr_reloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 17:44:29 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/07 17:53:53 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_calc_tkns	*calc_reloc_tkns(t_calc_tkns *s_tokens)
{
	t_calc_tkn		*new_tokens;

	if (!s_tokens)
		return (NULL);
	if (!(new_tokens = (t_calc_tkn *)malloc(sizeof(t_calc_tkn)
		* (s_tokens->malloc_size + CALC_TOKENS_SIZE))))
		return (s_tokens);
	new_tokens = ft_memcpy(new_tokens, s_tokens->tokens, sizeof(t_calc_tkn)
		* s_tokens->malloc_size);
	free(s_tokens->tokens);
	s_tokens->tokens = new_tokens;
	s_tokens->malloc_size += CALC_TOKENS_SIZE;
	return (s_tokens);
}
