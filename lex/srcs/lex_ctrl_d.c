/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_ctrl_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 21:41:53 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/12 20:41:01 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "builtins.h"

t_lex_fr		lex_cs_ctrl_d(char **s1, char is_quotes)
{
	if (is_quotes)
		err("42sh", "syntax error", NULL, EUEOF);
	lex_clear_strs(s1, NULL);
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

t_lex_tkn_type	lex_al_ctrl_d(char **s1)
{
	err("42sh", "syntax error", NULL, EUEOF);
	lex_clear_strs(s1, NULL);
	return (T_CTRL_D);
}
