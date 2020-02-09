/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_val_tkn_processing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:35:34 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/09 17:15:45 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static int		lex_is_one_clip(t_lex_tkn_type type)
{
	if (type == T_ROUND_SUB || type == T_FIGURE_SUB || type == T_QUOTES)
		return (1);
	else
		return (0);
}

static int		lex_is_double_clip(t_lex_tkn_type type)
{
	if (type == T_ARITH_SUB)
		return (1);
	return (0);
}

void			lex_clipping_tkn_value(t_lex_tkn *token, const char *str)
{
	size_t	offset;
	size_t	start_pos;
	size_t	end_pos;
	size_t	len;

	offset = 0;
	lex_rewind_end_spases((char *)str, &token->end_pos);
	if (lex_is_one_clip(token->type))
		offset = 1;
	else if (lex_is_double_clip(token->type))
		offset = 2;
	token->type = (token->type == T_QUOTES) ? T_WORD : token->type;
	start_pos = token->start_pos + offset;
	end_pos = token->end_pos - offset;
	len = end_pos - start_pos;
	if (!offset)
	{
		lex_rewind_end_spases((char *)str, &token->end_pos);
		len = token->end_pos - start_pos;
		token->value = ft_strsub(str, start_pos, len);
		return ;
	}
	token->value = ft_strsub(str, start_pos, len);
}
