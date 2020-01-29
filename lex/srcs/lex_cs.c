/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_cs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:11:31 by ggrimes           #+#    #+#             */
/*   Updated: 2020/01/29 22:29:00 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static t_lex_tkn_type	lex_cs_type(t_lex_cs_type type)
{
	if (type <= CS_DOUBLE_QUOTES && type >= CS_BACK_QUOTES)
		return (T_WORD);
	else if (type == CS_ROUND_BRK)
		return (T_ROUND_SUB);
	else if (type == CS_FIGURE_BRK)
		return (T_FIGURE_SUB);
	else if (type == CS_D_ROUND_BRK)
		return (T_ARITH_OPERS);
	else
		return (T_NULL);
}

static int				lex_cs_add_line(char **str, t_lex_cs_type type)
{
	char	*new_line;

	if (type >= CS_DOUBLE_QUOTES && type <= CS_BACK_QUOTES)
		if (!(*str = lex_add_eol(*str)))
			return (0);
	if (!(new_line = ft_readline(get_env("PS2", ALL_ENV))))
		return (0);
	if (*new_line == RL_K_CTRL_C)
		return (lex_ctrl_c(str, &new_line));
	if (!(*str = lex_strjoin(*str, new_line)))
		return (0);
	return (1);
}

static int				lex_is_cs_open(const char *str,
	int *cs_count, size_t *offset)
{
	if (!str || !offset)
		return (-1);
	while (str[*offset])
	{
		if (!lex_cs_inc_dec(str, cs_count, offset))
			return (-1);
		if (*cs_count == -1)
			break ;
	}
	if (*cs_count == -1)
		return (0);
	return (1);
}

t_lex_tkn_type			lex_cs(char **str, size_t *pos, t_lex_cs_type type)
{
	size_t	offset;
	int		cs_count;
	int		check;

	if (!str || !pos)
		return (T_ERR);
	offset = 0;
	cs_count = -1;
	while ((check = lex_is_cs_open((*str) + *pos, &cs_count, &offset)) == 1)
	{
		if (check == -1)
			return (T_ERR);
		if (!lex_cs_add_line(str, type))
			return (T_ERR);
	}
	(*pos) += offset;
	return ((check == -1) ? T_ERR : lex_cs_type(type));
}
