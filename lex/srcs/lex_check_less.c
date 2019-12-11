/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_less.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 20:29:41 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/10 22:40:02 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_check_less(char **str, short is_word, size_t *pos)
{
	if (is_word)
		return (T_NULL);
	else if (lex_is_less_and(*str, pos))
		return (T_LESS_AND);
	else if (lex_is_less_less(*str, pos))
		return (T_LESS_LESS);
	else
	{
		(*pos)++;
		return (T_LESS);
	}
}

int				lex_is_less_and(char *str, size_t *pos)
{
	if (!ft_strncmp(str + *pos, "<&", 2))
	{
		(*pos) += 2;
		return 1;
	}
	return (0);
}

int				lex_is_less_less(char *str, size_t *pos)
{
	if (!ft_strncmp(str + *pos, "<<", 2))
	{
		(*pos) += 2;
		return 1;
	}
	return (0);
}
