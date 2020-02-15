/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quotation_marks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 14:21:40 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/15 22:46:19 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int				lex_is_quotation_marks(char *str, size_t pos)
{
	if (str[pos] == '"' || str[pos] == '\'')
		return (1);
	return (0);
}

t_lex_tkn_type	lex_quotation_marks(char **str, short is_word, size_t *pos)
{
	t_lex_tkn_type	result;

	if (!(*str) || !pos)
		return (T_ERR);
	result = T_ERR;
	if ((*str)[*pos] == '"')
		result = lex_double_quotes(str, pos);
	else if ((*str)[*pos] == '\'')
		result = lex_single_quotes(str, pos);
	if (result == T_ERR)
		return (T_ERR);
	if (result == T_WORD && is_word
		&& ((*str)[*pos] == ' ' || !(*str)[*pos]))
		return (T_NULL);
	return (result);
}
