/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_val_tkn_processing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:35:34 by ggrimes           #+#    #+#             */
/*   Updated: 2020/01/30 22:35:36 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static int		lex_is_one_clip(const char *str, size_t pos, t_lex_tkn_type type)
{
	if (!str)
		return (0);
	if (type == T_ROUND_SUB || type == T_FIGURE_SUB)
		return (1);
	else if (type == T_WORD
		&& (str[pos] == '"' || str[pos] == '\'' || str[pos] == '`'))
		return (1);
	else
		return (0);
}

static int		lex_is_double_clip(const char *str, size_t pos, t_lex_tkn_type type)
{
	(void)str;
	(void)pos;
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
	if (lex_is_one_clip(str, token->start_pos, token->type))
		offset = 1;
	else if (lex_is_double_clip(str, token->start_pos, token->type))
		offset = 2;
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
