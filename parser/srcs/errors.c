/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:45:45 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/15 19:11:34 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "interpretator.h"

int		syntax_err(t_lex_tkn *token)
{
	ft_putstr("42sh: ");
	ft_putstr("syntax error near unexpected token: ");
	ft_putchar('`');
	if (token->value)
		ft_putstr(token->value);
	else
	{
		if (token->type == T_END)
			ft_putstr("end of line");
	}
	ft_putchar('\'');
	ft_putchar('\n');
	g_last_exit_status = 1;
	set_var("?", "1", VARS);
	return (-1);
}
