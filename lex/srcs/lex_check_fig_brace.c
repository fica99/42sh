/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_fig_brace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 22:38:02 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/19 23:01:38 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_check_fig_brace(char **str, short is_word, size_t *pos)
{
	if (is_word)
		return (T_NULL);
	else if ((*str)[*pos] == '{')
	{
		(*pos)++;
		return (T_OPEN_FIG_BRACE);
	}
	else
	{
		(*pos)++;
		return (T_CLOSE_FIG_BRACE);
	}
}
