/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: work <work@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:27:21 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/11 14:43:54 by work             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static t_lex_tkn_type	lex_pipe(char **str, size_t *pos)
{
	char	*new_line;
	size_t	offset;

	if (!str || !*str)
		return (0);
	offset = 0;
	while (lex_is_fin_log_oper(*str, *pos, &offset))
	{
		if (!(new_line = ft_readline(get_var("PS2", ALL_VARS))))
			return (T_ERR);
		if (*new_line == RL_K_CTRL_C)
			return (lex_ctrl_c(str, &newline));
		if (*new_line == RL_K_CTRL_D)
			return (lex_al_ctrl_d(&new_line));
		if (!(*str = lex_strjoin(*str, new_line)))
			return (T_ERR);
	}
	(*pos)++;
	return (T_PIPE);
}

t_lex_tkn_type			lex_check_or(char **str, short is_word, size_t *pos)
{
	t_lex_tkn_type	type;

	if (is_word)
		return (T_NULL);
	else if ((type = lex_is_or_or(str, *pos)) == T_OR_OR)
		return (lex_check_or_or(str, is_word, pos));
	else if (type == T_ERR)
		return (T_ERR);
	else if (type == T_CTRL_C)
		return (T_CTRL_C);
	else
		return (lex_pipe(str, pos));
}
