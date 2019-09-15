/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olegmulko <olegmulko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:25:54 by ggrimes           #+#    #+#             */
/*   Updated: 2019/09/18 15:25:21 by olegmulko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		print_token(t_string *str)
{
	t_token	*token;

	while (1)
	{
		if (!(token = get_next_token(str, g_lexer)))
			return ;
		if (token->type == FT_ERROR)
		{
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
			lx_clear_token(&token);
			return ;
		}
		if (token->type == EOL)
		{
			ft_putstr("EOF");
			ft_putchar('\n');
			lx_clear_token(&token);
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
		lx_clear_token(&token);
	}
}

void		print_matrix(t_matrix *matrix)
{
	int	i;
	int	j;

	i = -1;
	if (!matrix)
		return ;
	while (++i < matrix->rows)
	{
		j = -1;
		while (++j < matrix->cols)
		{
		ft_putnbr(matrix->data[i][j]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}
