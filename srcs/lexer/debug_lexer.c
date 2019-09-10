/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:25:54 by ggrimes           #+#    #+#             */
/*   Updated: 2019/09/14 15:12:11 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		print_token(t_string *str)
{
	t_token	*token;

	if (!(token = get_next_token(str, g_lexer)))
		return ;
	ft_putchar('\n');
	ft_putstr("lexeme: ");
	ft_putstr(token->lexeme);
	ft_putchar('\n');
	ft_putstr("type: ");
	ft_putnbr(token->type);
	ft_putchar('\n');
	ft_putstr("class: ");
	ft_putnbr(token->class);
	ft_putchar('\n');
	clear_token(&token);
	while (1)
	{
		if (!(token = get_next_token(str, g_lexer)))
			return ;
		if (token->type == FT_ERROR)
		{
			ft_putstr("Error");
			ft_putchar('\n');
			clear_token(&token);
			return ;
		}
		if (token->type == EOL)
		{
			ft_putstr("EOF");
			ft_putchar('\n');
			clear_token(&token);
			return ;
		}
		ft_putstr("lexeme: ");
		ft_putstr(token->lexeme);
		ft_putchar('\n');
		ft_putstr("type: ");
		ft_putnbr(token->type);
		ft_putchar('\n');
		ft_putstr("class: ");
		ft_putnbr(token->class);
		ft_putchar('\n');
		clear_token(&token);
	}
}