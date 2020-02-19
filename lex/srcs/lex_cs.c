/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_cs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:11:31 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/19 16:37:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static t_lex_fr		lex_cs_add_line(char **str)
{
	char	*new_line;

	if (!(new_line = ft_readline(get_var("PS2", ALL_VARS))))
		return (FR_ERR);
	if (*new_line == RL_K_CTRL_C)
		return (lex_cs_ctrl_c(str, &new_line));
	if (*new_line == RL_K_CTRL_D)
		return (lex_cs_ctrl_d(0, &new_line));
	if (!(*str = lex_strjoin(*str, new_line)))
		return (FR_ERR);
	return (FR_TRUE);
}

static t_lex_fr		lex_is_cs_open(char **str,
	int *cs_count, size_t *offset)
{
	t_lex_fr	fr;

	if (!str || !*str || !offset)
		return (FR_ERR);
	fr = FR_ERR;
	while ((*str)[*offset])
	{
		if ((fr = lex_cs_inc_dec(*str, cs_count, offset)) == FR_ERR)
			return (FR_ERR);
		if (*cs_count == -1)
			return (FR_FALSE);
		(*offset)++;
	}
	return (FR_TRUE);
}

t_lex_fr			lex_cs(char **str, size_t *pos)
{
	size_t		offset;
	int			cs_count;
	t_lex_fr	fr;

	if (!str || !pos)
		return (FR_ERR);
	offset = *pos;
	cs_count = -1;
	while ((fr = lex_is_cs_open(str, &cs_count, &offset)) == FR_TRUE)
	{
		if ((fr = lex_cs_add_line(str)) == FR_ERR)
			return (FR_ERR);
		if (fr == FR_CTRL_C || fr == FR_CTRL_D)
			return (fr);
	}
	if (fr == FR_ERR)
		return (FR_ERR);
	(*pos) = offset + 1;
	return (FR_TRUE);
}
