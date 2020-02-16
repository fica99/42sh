/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_asig_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 20:22:50 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/16 16:07:42 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static int		lex_is_an_sep(char c)
{
	if (c == ' ' || c == ';')
		return (1);
	return (0);
}

static t_lex_fr	lex_an_quotes(char **str, size_t *pos, int *err)
{
	t_lex_tkn_type	quotes_result;

	if ((*str)[*pos] == '"')
		quotes_result = lex_cs(str, pos, CS_DOUBLE_QUOTES);
	else if ((*str)[*pos] == '\'')
		quotes_result = lex_cs(str, pos, CS_SINGLE_QUOTES);
	else
		quotes_result = T_ERR;
	if (quotes_result == T_ERR)
	{
		*err = 1;
		return (FR_ERR);
	}
	if (quotes_result == T_CTRL_C)
		return (FR_CTRL_C);
	return (FR_OK);
}

t_lex_fr		lex_is_asig_name(char **str, short is_word, size_t *pos,
	int *err)
{
	size_t		i;

	if (!str || !*str)
		return (FR_ERR);
	i = *pos;
	while (ft_isalnum((*str)[i]) || (*str)[i] == '_')
		i++;
	if ((*str)[i++] != '=')
		return (FR_NULL);
	if (lex_is_quotation_marks(*str, i))
		lex_an_quotes(str, &i, err);
	else
		while ((*str)[i] && !lex_is_an_sep((*str)[i]))
			i++;
	if (!is_word)
		(*pos) = i;
	return (FR_OK);
}

t_lex_tkn_type	lex_asig_name(short is_word, int err, t_lex_fr fr)
{
	if (err || fr == FR_ERR)
		return (T_ERR);
	else if (fr == FR_CTRL_C)
		return (T_CTRL_C);
	if (is_word)
		return (T_NULL);
	return (T_ASSIGNMENT_WORD);
}
