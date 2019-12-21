/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_dol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 21:17:04 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/19 23:53:15 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_check_dol(char **str, short is_word, size_t *pos)
{
	int			err;

	err = 0;
	if (!str || !pos)
		return (T_ERR);
	else if (lex_is_arith_opers(*str, is_word, pos, &err))
		return (lex_arith_opers(is_word, err));
	else if (lex_is_control_sub(*str, is_word, pos, &err))
		return (lex_control_sub(is_word, err));
	else
	{
		(*pos)++;
		return (T_WORD);
	}
}
