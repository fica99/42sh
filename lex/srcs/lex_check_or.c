/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:27:21 by ggrimes           #+#    #+#             */
/*   Updated: 2020/01/20 22:26:32 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_check_or(char **str, short is_word, size_t *pos)
{
	if (is_word)
		return (T_NULL);
	else if (lex_is_or_or(str, *pos))
		return (lex_check_or_or(str, is_word, pos));
	else
	{
		(*pos)++;
		return (T_PIPE);
	}
}
