/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:16:25 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/21 15:00:17 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

void		calc_print_tkn(t_calc_tkn *token)
{
	if (!token)
		return ;
	ft_putchar('\n');
	ft_putstr("********************\n");
	if (!token)
	{
		ft_putstr("token = NULL\n");
		return ;
	}
	if (token->type != CALC_VAR)
	{
		ft_putstr("token->value = ");
		ft_putstr((char *)token->value);
		ft_putchar('\n');
	}
	else
		calc_print_var(token);
	ft_putstr("token-type = ");
	calc_print_type(token->type);
	ft_putstr("token->start_pos = ");
	ft_putnbr(token->start_pos);
	ft_putchar('\n');
	ft_putstr("token->end_pos = ");
	ft_putnbr(token->end_pos);
	ft_putchar('\n');
	ft_putstr("********************\n");
}

void		calc_print_var(t_calc_tkn *token)
{
	t_calc_var	*var;

	var = (t_calc_var *)token->value;
	ft_putstr("var->value= ");
	ft_putstr(var->value);
	ft_putchar('\n');
	ft_putstr("var->size = ");
	ft_putnbr((int)var->size);
	ft_putchar('\n');
}

void		calc_print_error(t_calc_err *error)
{
	if (!error)
		return ;
	ft_putchar('\n');
	ft_putstr("********************\n");
	ft_putstr("error->status = ");
	if (error->status)
		ft_putstr("TRUE\n");
	else
		ft_putstr("FALSE\n");
	calc_print_errro_type(error->type);
	ft_putstr("********************\n");
}

void		calc_print_errro_type(t_calc_err_type type)
{
	ft_putstr("error->type = ");
	if (type == CALC_ERR_NULL_OR_IND)
		ft_putstr("INDEX ERROR");
	else if (type == CALC_ERR_LX)
		ft_putstr("LEXER ERROR");
	else if (type == CALC_ERR_SYNTAX)
		ft_putstr("SYNTAX ERROR");
	else if (type == CALC_ERR_DIV_ZERO)
		ft_putstr("DIVISION BY ZERO");
	else if (type == CALC_ERR_PARENT)
		ft_putstr("PARENT ERROR");
	ft_putchar('\n');
}

void		calc_print_tkns(t_calc_tkns	*s_tokens)
{
	size_t		i;

	if (!s_tokens)
		return ;
	i = -1;
	while(++i < s_tokens->size)
		calc_print_tkn(&s_tokens->tokens[i]);
	return ;
}

void		calc_print_type(t_calc_tkntype type)
{
	if (type == CALC_ERROR)
		ft_putstr("ERROR\n");
	else if (type == CALC_END)
		ft_putstr("END\n");
	else if (type == CALC_NUMBER)
		ft_putstr("NUMBER\n");
	else if (type == CALC_PLUS)
		ft_putstr("PLUS\n");
	else if (type == CALC_MINUS)
		ft_putstr("MINUS\n");
	else if (type == CALC_MUL)
		ft_putstr("MUL\n");
	else if (type == CALC_DIV)
		ft_putstr("DIV\n");
	else if (type == CALC_MOD)
		ft_putstr("MOD\n");
	else if (type == CALC_INC)
		ft_putstr("INC\n");
	else if (type == CALC_DEC)
		ft_putstr("DEC\n");
	else if (type == CALC_LESS)
		ft_putstr("LESS\n");
	else if (type == CALC_MORE)
		ft_putstr("MORE\n");
	else if (type == CALC_LESSOREQ)
		ft_putstr("LESSOREQ\n");
	else if (type == CALC_MOREOREQ)
		ft_putstr("MOREOREQ\n");
	else if (type == CALC_EQ)
		ft_putstr("EQ\n");
	else if (type == CALC_DIFF)
		ft_putstr("DIFF\n");
	else if (type == CALC_AND)
		ft_putstr("AND\n");
	else if (type == CALC_OR)
		ft_putstr("OR\n");
	else if (type == CALC_LPARENT)
		ft_putstr("LPARENT\n");
	else if (type == CALC_RPARENT)
		ft_putstr("RPARENT\n");
	else if (type == CALC_VAR)
		ft_putstr("VAR\n");
	else
		ft_putstr("UNDEFINED\n");
}

void	calc_putnbr(long long n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if (n >= 10)
		calc_putnbr(n / 10);
	ft_putchar((n % 10) + '0');
}
