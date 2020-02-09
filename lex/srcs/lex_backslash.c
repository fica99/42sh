/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_backslash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 08:49:45 by olegmulko         #+#    #+#             */
/*   Updated: 2020/02/09 20:47:37 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static void			lex_esc_char(const char *str, size_t *pos)
{
	if (!str)
		return ;
	if (str[*pos] == '\\')
		(*pos)++;
	if (str[*pos] == '"' || str[*pos] == '\''
		|| str[*pos] == '`' || str[*pos] == '\\')
		(*pos)++;
}

static t_lex_fr		lex_add_line_bs(char **str)
{
	char			*new_line;

	if (!(new_line = ft_readline(get_var("PS2", ALL_VARS))))
		return (FR_ERR);
	if (*new_line == RL_K_CTRL_C)
		return (lex_cs_ctrl_c(str, &new_line));
	if (!(*str = lex_strjoin(*str, new_line)))
		return (FR_ERR);
	return (FR_OK);
}

static int			lex_bs_is_fin(const char *str, size_t pos)
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

t_lex_fr			lex_bs(char **str, size_t *pos)
{
	t_lex_fr		al_result;

	if (!str || !*str)
		return (FR_ERR);
	al_result = FR_OK;
	if ((*str)[*pos] != '\\')
		return (FR_OK);
	if (lex_bs_is_fin(*str, *pos))
		if ((al_result = lex_add_line_bs(str)) == FR_ERR)
			return (FR_ERR);
	if (al_result == FR_CTRL_C)
		return (FR_CTRL_C);
	lex_esc_char(*str, pos);
	if (!(*str)[*pos])
		return (FR_EOL);
	return (FR_OK);
}

t_lex_tkn_type		lex_check_bs(char **str, size_t *pos)
{
	int				bs_result;

	if (!(*str) || !pos)
		return (T_ERR);
	if ((bs_result = lex_bs(str, pos)) == FR_ERR)
		return (T_ERR);
	if (bs_result == FR_CTRL_C)
		return (T_CTRL_C);
	return (T_WORD);
}
