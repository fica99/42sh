/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_and.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 23:17:51 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/17 23:23:53 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_check_and(char **str, short is_word, size_t *pos)
{
	if (lex_is_and_and(*str, *pos))
		return (lex_check_and_and(str, is_word, pos));
	(*pos)++;
	return (T_WORD);
}
