/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_greater.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:07:33 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/12 22:02:01 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_check_greater(char **str, short is_word, size_t *pos)
{
	if (is_word)
		return (T_NULL);
	else if (lex_is_greater_and(*str, pos))
		return (T_GREATER_AND);
	else if (lex_is_greater_greater(*str, pos))
		return (T_GREATER_GREATER);
	else
	{
		(*pos)++;
		return (T_GREATER);
	}
}

int				lex_is_greater_and(char *str, size_t *pos)
{
	if (!ft_strncmp(str + *pos, ">&", 2))
	{
		(*pos) += 2;
		return (1);
	}
	return (0);
}

int				lex_is_greater_greater(char *str, size_t *pos)
{
	if (!ft_strncmp(str + *pos, ">>", 2))
	{
		(*pos) += 2;
		return (1);
	}
	return (0);
}
