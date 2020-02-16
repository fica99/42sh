/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_log_opers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 22:57:42 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/16 15:49:08 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_is_and_and(char **str, size_t pos)
{
	if (!str || !*str)
		return (0);
	if (ft_strncmp(*str + pos, "&&", 2))
		return (T_NULL);
	return (T_AND_AND);
}

t_lex_tkn_type	lex_check_and_and(char **str, short is_word, size_t *pos)
{
	(void)str;
	if (is_word)
		return (T_NULL);
	(*pos) += 2;
	return (T_AND_AND);
}

t_lex_tkn_type	lex_is_or_or(char **str, size_t pos)
{
	if (!str || !*str)
		return (0);
	if (ft_strncmp(*str + pos, "||", 2))
		return (T_NULL);
	return (T_OR_OR);
}

t_lex_tkn_type	lex_check_or_or(char **str, short is_word, size_t *pos)
{
	(void)str;
	if (is_word)
		return (T_NULL);
	(*pos) += 2;
	return (T_OR_OR);
}

int				lex_is_fin_log_oper(char *str, size_t pos, size_t *offset)
{
	if (!str || !offset)
		return (0);
	while (str[pos + *offset])
	{
		if (!ft_strncmp(str + pos + *offset, "||", 2)
			|| !ft_strncmp(str + pos + *offset, "&&", 2)
			|| str[pos + *offset] == '|')
		{
			if (!ft_strncmp(str + pos + *offset, "||", 2)
				|| !ft_strncmp(str + pos + *offset, "&&", 2))
				(*offset)++;
			(*offset)++;
			while (ft_isspace(str[pos + *offset]))
				(*offset)++;
			if (!str[pos + *offset])
				return (1);
		}
		(*offset)++;
	}
	return (0);
}
