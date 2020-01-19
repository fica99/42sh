/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_single_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 19:42:12 by ggrimes           #+#    #+#             */
/*   Updated: 2020/01/20 21:25:45 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_type	lex_single_quotes(char **str, size_t *pos)
{
	char	*new_line;
	size_t	offset;

	if (!str || !pos)
		return (T_ERR);
	offset = 1;
	while (lex_is_open_sq(*str, *pos, &offset))
	{
		if (!(*str = lex_add_eol(*str)))
			return (T_ERR);
		if (!(new_line = ft_readline(get_env("PS2", ALL_ENV), EMACS)))
			return (T_ERR);
		if (!(*str = lex_strjoin(*str, new_line)))
			return (T_ERR);
	}
	(*pos) += offset + 1;
	return (T_NULL);
}

int				lex_is_open_sq(char *str, size_t pos, size_t *offset)
{
	if (!str || !offset)
		return (0);
	while (str[pos + *offset])
	{
		if (str[pos + *offset] == '\'')
			if (!lex_is_esc_dq(str, pos + *offset))
				return (0);
		(*offset)++;
	}
	return (1);
}

size_t			lex_is_esc_sq(char *str, size_t pos)
{
	if (!str)
		return (0);
	if (pos > pos - 1)
		if (!ft_strncmp(str + pos - 1, "\\'", 2))
			return (1);
	return (0);
}
