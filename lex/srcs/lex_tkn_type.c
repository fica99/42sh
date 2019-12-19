/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tkn_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:34:00 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/19 22:47:38 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type		lex_check_type(char **str, short is_word, size_t *pos)
{
	if (lex_is_quote((*str)[*pos]))
		if (!lex_check_quotes(*str, pos))
			return (T_ERR);
	if (!(*str)[*pos])
		return (lex_check_end(str, is_word, pos));
	else if ((*str)[*pos] == ' ')
		return (T_NULL);
	else if (ft_isalnum((*str)[*pos]))
		return (lex_check_alnum(str, is_word, pos));
	else if ((*str)[*pos] == '|')
		return (lex_check_or(str, is_word, pos));
	else if ((*str)[*pos] == '>')
		return (lex_check_greater(str, is_word, pos));
	else if ((*str)[*pos] == '<')
		return (lex_check_less(str, is_word, pos));
	else if ((*str)[*pos] == '&')
		return (lex_check_and(str, is_word, pos));
	else if ((*str)[*pos] == ';')
		return (lex_check_sep(str, is_word, pos));
	else if ((*str)[*pos] == '$')
		return (lex_check_dol(str, is_word, pos));
	else if ((*str)[*pos] == '{' || (*str)[*pos] == '}')
		return (lex_check_fig_brace(str, is_word, pos));
	else
		return (lex_check_other(str, is_word, pos));
}
