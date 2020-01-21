/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_and.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 23:17:51 by ggrimes           #+#    #+#             */
/*   Updated: 2020/01/21 22:10:23 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_check_and(char **str, short is_word, size_t *pos)
{
	t_lex_tkn_type	type;

	if (is_word)
		return (T_NULL);
	else if ((type = lex_is_and_and(str, *pos)) == T_AND_AND)
		return (lex_check_and_and(str, is_word, pos));
	else if (type == T_ERR)
		return (T_ERR);
	else if (type == T_CTRL_C)
		return (T_CTRL_C);
	else
	{
		(*pos)++;
		return (T_AND);
	}
}
