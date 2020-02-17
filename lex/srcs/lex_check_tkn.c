/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_tkn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 15:37:30 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/17 21:33:19 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_check_other(char **str, short is_word, size_t *pos)
{
	(void)str;
	(void)is_word;
	(*pos)++;
	return (T_WORD);
}

t_lex_tkn_type	lex_check_end(char **str, short is_word, size_t *pos)
{
	(void)str;
	if (is_word)
		return (T_NULL);
	(*pos)++;
	return (T_END);
}

t_lex_tkn_type	lex_check_alnum(char **str, short is_word, size_t *pos)
{
	t_lex_fr	fr;

	if (lex_is_ionum(*str, is_word, pos))
		return (lex_ionum(is_word));
	else if ((fr = lex_is_asig_name(str, is_word, pos)) != FR_FALSE)
		return (lex_asig_name(is_word, fr));
	else
	{
		(*pos)++;
		return (T_WORD);
	}
}
