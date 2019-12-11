/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_tkn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 15:37:30 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/10 22:37:59 by ggrimes          ###   ########.fr       */
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
	(void)pos;
	if (is_word)
		return (T_NULL);
	return (T_END);
}

t_lex_tkn_type	lex_check_alnum(char **str, short is_word, size_t *pos)
{
	if (is_word && lex_is_ionum(*str, is_word, pos))
		return (T_NULL);
	else if (!is_word && lex_is_ionum(*str, is_word, pos))
		return (T_IO_NUMBER);
	else
	{
		(*pos)++;
		return (T_WORD);
	}
}
