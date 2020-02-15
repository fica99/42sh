/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expantions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 23:22:05 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/15 23:50:10 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type		lex_expantions(char **str, size_t *pos)
{
	size_t			new_pos;
	t_lex_tkn_type	result;

	if (!(*str) || !pos)
		return (T_ERR);
	new_pos = *pos;
	if ((result = lex_cs(str, &new_pos, CS_FIGURE_BRK)) == T_ERR)
		return (T_ERR);
	(*pos)++;
	return (result);
}
