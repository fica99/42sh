/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_pipes_log_opers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:49:52 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/17 23:05:18 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static t_lex_tkn	**lo_p_ctrl(t_lex_tkn **tkns, char *line)
{
	free(line);
	if (tkns)
	{
		err("42sh", "syntax error", NULL, EUEOF);
		lex_del_tkns(tkns);
		return (NULL);
	}
	return (tkns);
}

t_lex_tkn			**al_p_lo(t_lex_tkn **src_tkns)
{
	char		*new_line;
	t_lex_tkn	**ins_tkns;
	t_lex_tkn	**result_tkns;
	size_t		src_tkns_size;

	while (!*(new_line = ft_readline(get_var("PS2", ALL_VARS))))
		free(new_line);
	if (*new_line == RL_K_CTRL_C)
		lo_p_ctrl(src_tkns, new_line);
	if (*new_line == RL_K_CTRL_D)
		lo_p_ctrl(NULL, new_line);
	if (!(ins_tkns = lex_get_tkns(&new_line)) && g_lex_stat != LS_OK)
	{
		lex_del_tkns(src_tkns);
		free(new_line);
		return (NULL);
	}
	src_tkns_size = lex_tkns_size(src_tkns);
	result_tkns = lex_insert_tkns(src_tkns, ins_tkns, src_tkns_size);
	free(ins_tkns);
	if (!result_tkns)
		lex_del_tkns(src_tkns);
	return (result_tkns);
}
