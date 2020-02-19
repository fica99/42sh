/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_pipes_log_opers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:49:52 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/20 00:20:22 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static int		lo_p_ctrl_c(char **line, char **new_line)
{
	ft_strdel(line);
	ft_strdel(new_line);
	return (1);
}

static int		lo_p_ctrl_d(char **new_line)
{
	ft_strdel(new_line);
	err("42sh", "syntax error", NULL, EUEOF);
	return (1);
}

int				al_p_lo(t_lex_tkn ***src_tkns, char **line)
{
	char		*new_line;
	t_lex_tkn	**ins_tkns;
	size_t		src_tkns_size;

	src_tkns_size = 0;
	while (!*(new_line = ft_readline(get_var("PS2", ALL_VARS))))
		free(new_line);
	if (*new_line == RL_K_CTRL_C)
		return (lo_p_ctrl_c(line, &new_line));
	if (*new_line == RL_K_CTRL_D)
		return (lo_p_ctrl_d(&new_line));
	if (!(ins_tkns = lex_get_tkns(&new_line)) && g_lex_stat != LS_OK)
	{
		if (g_lex_stat != LS_CTRL_D)
			lex_del_tkns(*src_tkns);
		free(new_line);
		return (1);
	}
	if (!(*line = lex_strjoin(*line, new_line)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	src_tkns_size = lex_tkns_size(*src_tkns);
	*src_tkns = lex_insert_tkns(*src_tkns, ins_tkns, src_tkns_size);
	return (0);
}
