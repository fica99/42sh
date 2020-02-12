/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_hist_exp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 23:20:02 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/12 23:24:48 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_check_hist_exp(char **str, size_t *pos)
{
	if (!(*str) || !pos)
		return (T_ERR);
	else if (lex_is_hist_exp(*str, *pos))
	{
		if (!lex_history_exp(str, *pos))
			return (T_ERR);
		return (T_WORD);
	}
	(*pos)++;
	return (T_WORD);
}
