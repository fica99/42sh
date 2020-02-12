/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_single_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 19:42:12 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/12 20:44:39 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static t_lex_fr	lex_is_open_sq(char **str, size_t pos, size_t *offset)
{
	if (!str || !*str || !offset)
		return (FR_ERR);
	while ((*str)[pos + *offset])
	{
		if (!ft_strncmp((*str) + pos + (*offset), "\\'", 2))
		{
			if (!(*str = lex_del_backslash(*str, pos + (*offset))))
				return (FR_ERR);
			(*offset)++;
		}
		if ((*str)[pos + *offset] == '\'')
			return (FR_NULL);
		if ((*str)[pos + (*offset)])
			(*offset)++;
	}
	return (FR_OK);
}

t_lex_tkn_type	lex_single_quotes(char **str, size_t *pos)
{
	char		*new_line;
	size_t		offset;
	t_lex_fr	fr;

	if (!str || !pos)
		return (T_ERR);
	offset = 1;
	while ((fr = lex_is_open_sq(str, *pos, &offset)) == FR_OK)
	{
		if (fr == FR_ERR)
			return (T_ERR);
		if (!(*str = lex_add_eol(*str)))
			return (T_ERR);
		if (!(new_line = ft_readline(get_var("PS2", ALL_VARS))))
			return (T_ERR);
		if (*new_line == RL_K_CTRL_C)
			return (lex_ctrl_c(str, &new_line));
		if (*new_line == RL_K_CTRL_D)
			return (lex_al_ctrl_d(&new_line));
		if (!(*str = lex_strjoin(*str, new_line)))
			return (T_ERR);
	}
	(*pos) += offset + 1;
	return (T_WORD);
}
