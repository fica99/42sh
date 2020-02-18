/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_ctrl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 21:41:53 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/17 23:19:39 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "builtins.h"
#include "interpretator.h"

t_lex_tkn_type	lex_ctrl_c(char **s1, char **s2)
{
	lex_clear_strs(s1, s2);
	set_var("?", "1", VARS);
	g_last_exit_status = 1;
	return (T_CTRL_C);
}

t_lex_fr		lex_cs_ctrl_c(char **s1, char **s2)
{
	lex_clear_strs(s1, s2);
	set_var("?", "1", VARS);
	g_last_exit_status = 1;
	return (FR_CTRL_C);
}

t_lex_fr		lex_cs_ctrl_d(char c)
{
	if (c != '"' && c != '\'')
		return (FR_CTRL_D);
	if (c == '"')
		err("42sh", NULL, NULL, EUEOFMDQ);
	else if (c == '\'')
		err("42sh", NULL, NULL, EUEOFMSQ);
	else
		err("42sh", "syntax error", NULL, EUEOF);
	return (FR_CTRL_D);
}

t_lex_tkn_type	lex_ctrl_d(void)
{
	char		**str;

	ft_putendl("exit");
	if (!(str = ft_darnew(1)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	if (!(str[0] = ft_strdup("exit")))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	exit_built(1, str, NULL);
	return (T_CTRL_D);
}

t_lex_tkn_type	lex_al_ctrl_d(char **s1, char c)
{
	if (c == '"')
		err("42sh", NULL, NULL, EUEOFMDQ);
	else if (c == '\'')
		err("42sh", NULL, NULL, EUEOFMSQ);
	else
		err("42sh", "syntax error", NULL, EUEOF);
	lex_clear_strs(s1, NULL);
	return (T_CTRL_D);
}
