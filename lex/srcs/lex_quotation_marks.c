/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quotation_marks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 14:21:40 by ggrimes           #+#    #+#             */
/*   Updated: 2020/01/19 17:25:08 by ggrimes          ###   ########.fr       */
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
	size_t	i;

	if (!(*str) || !pos)
		return (T_ERR);
	if (is_word)
		return (T_NULL);
	else if ((*str)[*pos] == '"')
		return (lex_double_quotes(str, pos));
	else
	{
		i = *pos + 1;
		while ((*str)[i] && !lex_is_quotation_marks(*str, i))
			i++;
		if (!(*str)[i])
			return (T_ERR);
		(*pos) = i;
		return (T_NULL);
	}
}
