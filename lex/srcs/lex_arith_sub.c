/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_arith_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: work <work@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 16:29:44 by work              #+#    #+#             */
/*   Updated: 2020/02/11 16:40:33 by work             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_arith_sub(char **str, short is_word, size_t *pos)
{
	if (!(*str) || !pos)
		return (T_ERR);
	else if (!ft_strncmp((*str) + (*pos), "$((", 3))
	{
		if (is_word)
			return (T_NULL);
		(*pos)++;
		return (lex_cs(str, pos, CS_D_ROUND_BRK));
	}
	else
		return (T_WORD);
}
