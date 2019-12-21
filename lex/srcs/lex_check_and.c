/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_and.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 23:17:51 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/19 22:30:49 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_check_and(char **str, short is_word, size_t *pos)
{
	if (is_word)
		return (T_NULL);
	else if (lex_is_and_and(*str, *pos))
		return (lex_check_and_and(str, is_word, pos));
	else
	{
		(*pos)++;
		return (T_AND);
	}
}
