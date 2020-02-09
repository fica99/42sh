/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quotation_marks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 14:21:40 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/09 17:17:20 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int				lex_is_quotation_marks(char *str, size_t pos)
{
	if (str[pos] == '"' || str[pos] == '`' || str[pos] == '\'')
		return (1);
	return (0);
}

t_lex_tkn_type	lex_quotation_marks(char **str, short is_word, size_t *pos)
{
	if (!(*str) || !pos)
		return (T_ERR);
	if (is_word)
		return (T_NULL);
	else if ((*str)[*pos] == '"')
		return (lex_cs(str, pos, CS_DOUBLE_QUOTES));
	else if ((*str)[*pos] == '\'')
		return (lex_cs(str, pos, CS_SINGLE_QUOTES));
	else if ((*str)[*pos] == '`')
		return (lex_cs(str, pos, CS_BACK_QUOTES));
	else
		return (T_ERR);
}
