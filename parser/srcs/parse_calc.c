/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:44:56 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/12 19:44:58 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "calc.h"
void    print_error(int err)
{
    ft_putstr_fd("42sh: calc: ", STDERR_FILENO);
    if (err == CALC_ERR_NULL_OR_IND)
        ft_putstr_fd("err null or ind", STDERR_FILENO);
    else if (err == CALC_ERR_LX)
        ft_putstr_fd("err lx", STDERR_FILENO);
	else if (err == CALC_ERR_NULL_OR_IND)
        ft_putstr_fd("sytax error", STDERR_FILENO);
    else if (err == CALC_ERR_NULL_OR_IND)
        ft_putstr_fd("division by zero", STDERR_FILENO);
	else if (err == CALC_ERR_NULL_OR_IND)
        ft_putstr_fd("err parent", STDERR_FILENO);
    else
        ft_putstr_fd("unexpected error", STDERR_FILENO);
}

void    parse_calc(t_lex_tkn **tkn)
{
    t_calc_err *error;
    long long num;
    
    error = NULL;
    num = calc((*tkn)->value, &error);
    if (error->status)
    {
        free(error);
        return (print_error(error->type));
    }
    free((*tkn)->value);
    (*tkn)->value = calc_ltoa(num);
}
