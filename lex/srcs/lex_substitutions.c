/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_substitutions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:35:14 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/09 13:31:17 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int				lex_is_brk(char c)
{
	if (c == '(' || c == ')'
		|| c == '{' || c == '}')
		return (1);
	return (0);
}

t_lex_tkn_type	lex_substitutions(char **str, short is_word, size_t *pos)
{
	if (!(*str) || !pos)
		return (T_ERR);
	if (is_word)
		return (T_NULL);
	else if (!ft_strncmp(*str, "((", 2))
		return (lex_cs(str, pos, CS_D_ROUND_BRK));
	else if ((*str)[*pos] == '(')
		return (lex_cs(str, pos, CS_ROUND_BRK));
	else if ((*str)[*pos] == '{')
		return (lex_cs(str, pos, CS_FIGURE_BRK));
	else
		return (T_ERR);
}
