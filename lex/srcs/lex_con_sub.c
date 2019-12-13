/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_con_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 21:37:00 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/12 22:04:08 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int				lex_is_control_sub(char *str, short is_word, size_t *pos,
	int *err)
{
	size_t	i;
	int		brk;

	i = *pos;
	brk = 0;
	if (str[i] == '$')
		i++;
	if (str[i++] != '(')
		return (0);
	brk++;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '(')
			brk++;
		if (str[i] == ')')
			brk--;
		i++;
	}
	if (brk)
		*err = 1;
	if (!is_word)
		*pos = i;
	return (1);
}

t_lex_tkn_type	lex_control_sub(short is_word, int err)
{
	if (err)
		return (T_ERR);
	if (is_word)
		return (T_NULL);
	return (T_CONTROL_SUB);
}
