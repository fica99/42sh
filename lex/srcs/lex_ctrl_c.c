/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_ctrl_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olegmulko <olegmulko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 20:17:48 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/08 11:40:07 by olegmulko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

void			lex_clear_strs(char **s1, char **s2)
{
	if (s1)
	{
		if (*s1)
		{
			free(*s1);
			*s1 = NULL;
		}
	}
	if (s2)
	{
		if (*s2)
		{
			free(*s2);
			*s2 = NULL;
		}
	}
}

t_lex_tkn_type	lex_ctrl_c(char **s1, char **s2)
{
	lex_clear_strs(s1, s2);
	return (T_CTRL_C);
}

t_lex_fc		lex_cs_ctrl_c(char **s1, char **s2)
{
	lex_clear_strs(s1, s2);
	return (FR_CTRL_C);
}
