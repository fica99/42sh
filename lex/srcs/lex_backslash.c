/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_backslash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 08:49:45 by olegmulko         #+#    #+#             */
/*   Updated: 2020/02/19 16:38:06 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static t_lex_fr		lex_esc_char(char **str, size_t *pos)
{
	if (!str || !*str)
		return (FR_ERR);
	if ((*str)[*pos] == '\\')
		(*pos) += 2;
	return (FR_TRUE);
}

static t_lex_fr		lex_add_line_bs(char **str, size_t pos)
{
	char			*new_line;

	if (!(new_line = ft_readline(get_var("PS2", ALL_VARS))))
		return (FR_ERR);
	if (*new_line == RL_K_CTRL_C)
		return (lex_cs_ctrl_c(str, &new_line));
	(*str)[pos] = '\0';
	if (*new_line == RL_K_CTRL_D)
		return (lex_cs_ctrl_d(0, &new_line));
	if (!(*str = lex_strjoin(*str, new_line)))
		return (FR_ERR);
	return (FR_TRUE);
}

static int			lex_bs_is_fin(const char *str, size_t pos)
{
	if (!str)
		return (0);
	if (str[pos] != '\\')
		return (0);
	pos++;
	while (ft_isspace(str[pos]))
		pos++;
	if (!str[pos])
		return (1);
	return (0);
}

t_lex_tkn_type		lex_bs(char **str, size_t *pos)
{
	t_lex_fr		al_result;

	if (!str || !*str)
		return (T_ERR);
	al_result = FR_ERR;
	if ((*str)[*pos] != '\\')
		return (T_WORD);
	if (lex_bs_is_fin(*str, *pos))
		if ((al_result = lex_add_line_bs(str, *pos)) == FR_ERR)
			return (T_ERR);
	if (al_result == FR_CTRL_C)
		return (T_CTRL_C);
	if (al_result == FR_CTRL_D)
		return (T_CTRL_D);
	if (lex_esc_char(str, pos) == FR_ERR)
		return (T_ERR);
	if (!(*str)[*pos])
		return (T_NULL);
	return (T_WORD);
}
