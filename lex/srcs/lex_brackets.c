/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_brackets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 23:07:45 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/17 23:15:02 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_check_brackets(char **str, size_t *pos)
{
	t_lex_fr	fr;

	fr = FR_FALSE;
	if ((*str)[*pos] == '{')
		fr = lex_cs(str, pos, CS_FIGURE_BRK);
	else if (!ft_strncmp((*str) + *pos, "((", 2))
		fr = lex_cs(str, pos, CS_D_ROUND_BRK);
	if (fr == FR_ERR)
		return (T_ERR);
	else if (fr == FR_CTRL_C)
		return (T_CTRL_C);
	else if (fr == FR_CTRL_D)
		return (T_CTRL_D);
	if (fr == FR_FALSE)
		(*pos)++;
	return (T_WORD);
}
