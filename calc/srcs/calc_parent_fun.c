/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_parent_fun.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 21:14:54 by ggrimes           #+#    #+#             */
/*   Updated: 2019/11/26 21:21:24 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

static t_calc_tkntype  calc_parent_type(char *str)
{
    if (!str)
        return (0);
    if (*str == '(')
        return  CALC_LPARENT;
    else if (*str == ')')
        return  CALC_RPARENT;    
    else
        return (0);            
}

t_calc_tkn  *calc_get_parent_tkn(char *str, size_t pos)
{
    t_calc_tkn      *token;
    t_calc_tkntype  type;

    if (!str)
        return (NULL);
    type = calc_parent_type(str); 
    if (!(token = calc_newtkn(NULL, type)))
        return (NULL);
    token->start_pos = pos;
    token->end_pos = pos + 1;
    return (token);
}