/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_backslash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olegmulko <olegmulko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 08:49:45 by olegmulko         #+#    #+#             */
/*   Updated: 2020/02/06 15:59:31 by olegmulko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static void		lex_esc_char(const char *str, size_t *pos)
{
	size_t	offset;

	if (!str)
		return ;
	offset = *pos;
	if (str[offset] == '\\')
		offset++;
	if (str[offset] == '"' || str[offset] == '\''
		|| str[offset] == '`' || str[offset] == '\\')
		*pos = offset + 1;
}

static int		lex_add_line_bs(char **str)
{
	char	*new_line;

	if (!(*str = lex_add_eol(*str)))
		return (-1);
	if (!(new_line = ft_readline(get_var("PS2", ALL_VARS))))
		return (-1);
	if (*new_line == RL_K_CTRL_C)
	{
		lex_clear_strs(str, &new_line);
		return (0);
	}
	if (!(*str = lex_strjoin(*str, new_line)))
		return (-1);
	return (1);
}

static int		lex_bs_is_fin(const char *str, size_t pos)
{
	if (!str)
		return (0);
	while (ft_isspace(str[pos]))
		pos++;
	if (str[pos] != '\\')
		return (0);
	pos++;
	while (ft_isspace(str[pos]))
		pos++;
	if (!str[pos])
		return (1);
	return (0);
}

int				lex_check_bs(char **str, size_t *pos)
{
	int	al_result;

	if (!str || !*str)
		return (-1);
	if ((*str)[*pos] != '\\')
		return (1);
	if (lex_bs_is_fin(*str, *pos))
		if ((al_result = lex_add_line_bs(str)) == -1)
			return (-1);
	if (al_result == 0)
		return (0);
	lex_esc_char(*str, pos);
	return (1);
}
