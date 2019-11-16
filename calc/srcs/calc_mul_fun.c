/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_mul_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 20:11:13 by ggrimes           #+#    #+#             */
/*   Updated: 2019/11/19 20:07:20 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

static t_calc_tkntype  calc_mul_type(char *str)
{
    if (!str)
        return (0);
    if (*str == '*')
        return  CALC_MUL;
    else if (*str == '/')
        return  CALC_DIV;
    else if (*str == '%')
        return CALC_MOD;    
    else
        return (0);            
}

t_calc_tkn  *calc_get_mul_tkn(char *str, size_t pos)
{
    t_calc_tkn      *token;
    t_calc_tkntype  type;

    if (!str)
        return (NULL);
    type = calc_mul_type(str); 
    if (!(token = calc_newtkn(NULL, type)))
        return (NULL);
    token->start_pos = pos;
    token->end_pos = pos + 1;
    return (token);
}