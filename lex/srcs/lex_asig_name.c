/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_asig_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 20:22:50 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/12 22:05:07 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int				lex_is_asig_name(char *str, short is_word, size_t *pos,
	int *err)
{
	size_t	i;

	if (!str)
		return (0);
	i = *pos;
	while (ft_isdigit(str[i++]))
		*err = 1;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] != '=')
		return (0);
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
