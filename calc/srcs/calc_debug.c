/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:16:25 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/01 16:34:39 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

void	calc_print_tkn(t_calc_tkn *token, t_variables *variables)
{
    int test;

    if (!token)
        return ;
    ft_putchar('\n');
    ft_putstr("********************\n");
    if (!token)
        ft_putstr("token = NULL\n");
    else
    {
        ft_putstr("token->value = ");
        if (token->type == CALC_VAR || token->type == CALC_PREFIXVAR)
        {
            test = *((int *)token->value);
            ft_putnbr(test);
            ft_putstr(" => variable = ");
            ft_putnbr(*((int *)variables->data[test].value));
        }
        else
            ft_putstr((char *)token->value);
        ft_putchar('\n');
        ft_putstr("token-type = ");
        calc_print_type(token->type);
        ft_putstr("token->start_pos = ");
        ft_putnbr(token->start_pos);
        ft_putchar('\n');
        ft_putstr("token->end_pos = ");
        ft_putnbr(token->end_pos);
        ft_putchar('\n');
    }
    ft_putstr("********************\n");
}

void    calc_print_tkns(char *str, t_variables *variables)
{
    t_calc_tkns	*s_tokens;
	size_t		i;

	variables = calc_get_variables();

	if (!(s_tokens = calc_get_arr_tkns(str, variables)))
	{
		ft_putstr("\nERROR\n");
		return ;
	}
	i = -1;
	while(++i < s_tokens->size)
		calc_print_tkn(&s_tokens->tokens[i], variables);
	calc_del_tkns(s_tokens);
	return ;
}

void    calc_print_type(t_calc_tkntype type)
{
    if (type == CALC_ERROR)
        ft_putstr("ERROR\n");
    else  if (type == CALC_END)
        ft_putstr("END\n");
    else  if (type == CALC_NUMBER)
        ft_putstr("NUMBER\n");
    else  if (type == CALC_PLUS)
        ft_putstr("PLUS\n");
    else  if (type == CALC_MINUS)
        ft_putstr("MINUS\n");
    else  if (type == CALC_MUL)
        ft_putstr("MUL\n");
    else  if (type == CALC_DIV)
        ft_putstr("DIV\n");
    else  if (type == CALC_MOD)
        ft_putstr("MOD\n");
    else  if (type == CALC_INC)
        ft_putstr("INC\n");
    else  if (type == CALC_DEC)
        ft_putstr("DEC\n");
    else  if (type == CALC_LESS)
        ft_putstr("LESS\n");
    else  if (type == CALC_MORE)
        ft_putstr("MORE\n");
    else  if (type == CALC_LESSOREQ)
        ft_putstr("LESSOREQ\n");
    else  if (type == CALC_MOREOREQ)
        ft_putstr("MOREOREQ\n");
    else  if (type == CALC_EQ)
        ft_putstr("EQ\n");
    else  if (type == CALC_DIFF)
        ft_putstr("DIFF\n");
    else  if (type == CALC_AND)
        ft_putstr("AND\n");
    else  if (type == CALC_DIFF)
        ft_putstr("OR\n");
    else  if (type == CALC_VAR)
        ft_putstr("VAR\n");
    else  if (type == CALC_PREFIXVAR)
        ft_putstr("PREFIXVAR\n");
    else  if (type == CALC_LPARENT)
        ft_putstr("LPARENT\n");
    else  if (type == CALC_RPARENT)
        ft_putstr("RPARENT\n");
    else
        ft_putstr("UNDEFINED\n");
}

t_variables *calc_get_variables(void)
{
    t_variables *variables;
    t_variable  *variable;
    size_t      size;
    int         *value;

    size = 2;
    if (!(variables = (t_variables *)malloc(sizeof(t_variable))))
        return (NULL);
    if (!(variable = (t_variable *)malloc(sizeof(t_variable) * size)))
        return (NULL);
    variables->size = size;
    variables->data = variable;
    if (!(value = (int *)malloc(sizeof(int))))
        return (NULL);
    *value = 10;
    if (!(variable[0].name = ft_strdup("test1")))
        return (NULL);
    variable[0].value = value;
    variable[0].type = VAR_INT;
    if (!(variable[1].name = ft_strdup("test2")))
        return (NULL);
    variable[1].value = ft_strdup("test");
    variable[1].type = VAR_STR;
    return (variables);
}