/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:49:47 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/26 17:57:14 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (-1);
}
