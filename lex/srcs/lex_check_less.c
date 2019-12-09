/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_less.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 20:29:41 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/08 20:35:07 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_check_less(char **str, short is_word, size_t *pos)
{
	if (is_word)
		return (T_NULL);
	else if (!ft_strncmp(*str + *pos, "<<", 2))
	{
		(*pos) += 2;
		return (T_LESS_LESS);
	}
	else if (!ft_strncmp(*str + *pos, "<&", 2))
	{
		(*pos) += 2;
		return (T_LESS_AND);
	}
	else
	{
		(*pos)++;
		return (T_LESS);
	}
}
