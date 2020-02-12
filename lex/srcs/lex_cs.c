/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_cs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:11:31 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/12 20:43:31 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static t_lex_tkn_type	lex_cs_type(t_lex_cs_type type)
{
	if (type == CS_DOUBLE_QUOTES && type == CS_SINGLE_QUOTES)
		return (T_WORD);
	else if (type == CS_ROUND_BRK)
		return (T_ROUND_SUB);
	else if (type == CS_FIGURE_BRK)
		return (T_FIGURE_SUB);
	else if (type == CS_D_ROUND_BRK)
		return (T_ARITH_SUB);
	else
		return (T_NULL);
}

static t_lex_fr			lex_cs_add_line(char **str, t_lex_cs_type type)
{
	char	*new_line;

	if (type == CS_DOUBLE_QUOTES && type == CS_SINGLE_QUOTES)
		if (!(*str = lex_add_eol(*str)))
			return (FR_ERR);
	if (!(new_line = ft_readline(get_var("PS2", ALL_VARS))))
		return (FR_ERR);
	if (*new_line == RL_K_CTRL_C)
		return (lex_cs_ctrl_c(str, &new_line));
	if (*new_line == RL_K_CTRL_D)
		return (lex_cs_ctrl_d(&new_line, 1));
	if (!(*str = lex_strjoin(*str, new_line)))
		return (FR_ERR);
	return (FR_OK);
}

static t_lex_fr			lex_is_cs_open(char **str,
	int *cs_count, size_t *offset)
{
	t_lex_fr	fr;

	if (!str || !*str || !offset)
		return (FR_ERR);
	fr = FR_OK;
	while ((*str)[*offset])
	{
		if ((fr = lex_cs_inc_dec(*str, cs_count, offset)) == FR_ERR)
			return (FR_ERR);
		if (fr == FR_DRBRK_OPEN)
			return (FR_OK);
		if (*cs_count == -1)
			return (FR_NULL);
	}
	return (FR_OK);
}

t_lex_tkn_type			lex_cs(char **str, size_t *pos, t_lex_cs_type type)
{
	size_t		offset;
	int			cs_count;
	t_lex_fr	fr;

	if (!str || !pos)
		return (T_ERR);
	offset = *pos;
	cs_count = -1;
	while ((fr = lex_is_cs_open(str, &cs_count, &offset)) == FR_OK)
	{
		if (fr == FR_ERR)
			return (T_ERR);
		if ((fr = lex_cs_add_line(str, type)) == FR_ERR)
			return (T_ERR);
		if (fr == FR_CTRL_C)
			return (T_CTRL_C);
		if (fr == FR_CTRL_D)
			return (T_CTRL_D);
	}
	(*pos) = offset;
	return ((fr == FR_ERR) ? T_ERR : lex_cs_type(type));
}
