/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 21:43:20 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/17 23:03:34 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static t_lex_fr	lex_is_open_q(char *str, size_t *pos, char c)
{
	if (!str || !pos)
		return (FR_ERR);
	while (str[*pos])
	{
		if (str[*pos] == '\\' && str[(*pos) + 1] == c)
			(*pos) += 2;
		if (str[*pos] == c)
		{
			(*pos)++;
			return (FR_FALSE);
		}
		if (str[*pos])
			(*pos)++;
	}
	return (FR_TRUE);
}

t_lex_fr		lex_quotes(char **str, size_t *pos, char c)
{
	char		*new_line;
	size_t		new_pos;
	t_lex_fr	fr;

	if ((*str)[*pos] != c)
		return (FR_FALSE);
	new_pos = (*pos) + 1;
	while ((fr = lex_is_open_q(*str, &new_pos, c)) == FR_TRUE)
	{
		if (fr == FR_ERR)
			return (FR_ERR);
		if (!(*str = lex_add_eol(*str)))
			return (FR_ERR);
		if (!(new_line = ft_readline(get_var("PS2", ALL_VARS))))
			return (FR_ERR);
		if (*new_line == RL_K_CTRL_C)
			return (lex_cs_ctrl_c(str, &new_line));
		if (*new_line == RL_K_CTRL_D)
			return (lex_cs_ctrl_d(c));
		if (!(*str = lex_strjoin(*str, new_line)))
			return (FR_ERR);
	}
	(*pos) = new_pos;
	return (FR_TRUE);
}

t_lex_tkn_type	lex_check_quotes(char **str, size_t *pos)
{
	t_lex_fr	fr;

	fr = FR_FALSE;
	if ((*str)[*pos] == '"')
		fr = lex_quotes(str, pos, '"');
	else if ((*str)[*pos] == '\'')
		fr = lex_quotes(str, pos, '\'');
	if (fr == FR_ERR)
		return (T_ERR);
	else if (fr == FR_CTRL_C)
		return (T_CTRL_C);
	else if (fr == FR_CTRL_D)
		return (T_CTRL_D);
	if (fr == FR_FALSE)
		(*pos)++;
	return (T_WORD);
}
