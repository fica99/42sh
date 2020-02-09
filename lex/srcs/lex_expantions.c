/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expantions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:28:52 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/09 22:43:00 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_expantions(char **str, short is_word, size_t *pos)
{
	t_lex_tkn_type	result;

	if (!(*str) || !pos)
		return (T_ERR);
	else if ((*str)[(*pos) + 1] != '{')
	{
		++(*pos);
		return (T_WORD);
	}
	else if (is_word)
		return (T_NULL);
	else
	{
		(*pos)++;
		if ((result = lex_cs(str, pos, CS_FIGURE_BRK)) == T_FIGURE_SUB)
			return (T_WORD);
		return (result);
	}
}
