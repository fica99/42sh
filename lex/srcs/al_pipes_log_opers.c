/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_pipes_log_opers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:49:52 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/19 22:19:18 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static int	lo_p_ctrl(t_lex_tkn **tkns, char *line)
{
	free(line);
	if (tkns)
	{
		err("42sh", "syntax error", NULL, EUEOF);
		lex_del_tkns(tkns);
		return (1);
	}
	return (1);
}

int			al_p_lo(t_lex_tkn ***src_tkns)
{
	char		*new_line;
	t_lex_tkn	**ins_tkns;
	size_t		src_tkns_size;
	t_lex_tkn	**tmp;

	src_tkns_size = 0;
	while (!*(new_line = ft_readline(get_var("PS2", ALL_VARS))))
		free(new_line);
	if (*new_line == RL_K_CTRL_C)
		return lo_p_ctrl(*src_tkns, new_line);
	if (*new_line == RL_K_CTRL_D)
		return lo_p_ctrl(NULL, new_line);
	if (!(ins_tkns = lex_get_tkns(&new_line)) && g_lex_stat != LS_OK)
	{
		if (g_lex_stat != LS_CTRL_D)
		lex_del_tkns(*src_tkns);
		free(new_line);
		return (1);
	}
	free(new_line);
	tmp = *src_tkns;
	src_tkns_size = lex_tkns_size(tmp);
	*src_tkns = lex_insert_tkns(tmp, ins_tkns, src_tkns_size);
	return (0);
}
