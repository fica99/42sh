/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_asig_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 20:22:50 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/27 18:53:32 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static int		lex_is_an_sep(char c)
{
	if (c == ' ' || c == ';')
		return (1);
	return (0);
}

int				lex_is_asig_name(char *str, short is_word, size_t *pos,
	int *err)
{
	size_t	i;

	if (!str)
		return (0);
	i = *pos;
	if (ft_isdigit(str[i]))
	{
		*err = 1;
		i++;
	}
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] != '=')
		return (0);
	else
		i++;
	while (str[i] && !lex_is_an_sep(str[i]))
		i++;
	if (!is_word)
		(*pos) = i;
	return (1);
}

t_lex_tkn_type	lex_asig_name(short is_word, int err)
{
	if (err)
		return (T_ERR);
	if (is_word)
		return (T_NULL);
	return (T_ASSIGNMENT_WORD);
}
