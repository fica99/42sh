/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tkn_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:34:00 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/17 23:33:02 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static t_lex_tkn_type	lex_check_type_next(char **str,
	short is_word, size_t *pos)
{
	if ((*str)[*pos] == '\\')
		return (lex_bs(str, pos));
	else if ((*str)[*pos] == '"' || (*str)[*pos] == '\'')
		return (lex_check_quotes(str, pos));
	else if (!ft_strncmp((*str) + *pos, "((", 2) || (*str)[*pos] == '{')
		return (lex_check_brackets(str, pos));
	else if ((*str)[*pos] == ';')
		return (lex_check_sep(str, is_word, pos));
	else if ((*str)[*pos] == RL_K_CTRL_D)
		return (lex_ctrl_d());
	else if ((*str)[*pos] == '!')
		return (lex_check_hist_exp(str, pos));
	else
		return (lex_check_other(str, is_word, pos));
}

t_lex_tkn_type			lex_check_type(char **str, short is_word, size_t *pos)
{
	if (!(*str)[*pos])
		return (lex_check_end(str, is_word, pos));
	else if (ft_isspace((*str)[*pos]))
		return (T_NULL);
	else if ((*str)[*pos] == RL_K_CTRL_C)
		return (lex_ctrl_c(str, NULL));
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
	else
		return (lex_check_type_next(str, is_word, pos));
}
