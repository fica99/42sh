/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_log_opers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 22:57:42 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/17 23:09:33 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int				lex_is_and_and(char *str, size_t pos)
{
	if (!str)
		return (0);
	str += pos;
	if (ft_strncmp(str, "&&", 2) != 0)
		return (0);
	return (1);
}

t_lex_tkn_type	lex_check_and_and(char **str, short is_word, size_t *pos)
{
	(void)str;
	if (is_word)
		return (T_NULL);
	(*pos) += 2;
	return (T_AND_AND);
}

int				lex_is_or_or(char *str, size_t pos)
{
	if (!str)
		return (0);
	str += pos;
	if (ft_strncmp(str, "||", 2) != 0)
		return (0);
	return (1);
}

t_lex_tkn_type	lex_check_or_or(char **str, short is_word, size_t *pos)
{
	(void)str;
	if (is_word)
		return (T_NULL);
	(*pos) += 2;
	return (T_OR_OR);
}
