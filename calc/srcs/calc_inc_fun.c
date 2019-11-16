/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_inc_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 20:58:29 by ggrimes           #+#    #+#             */
/*   Updated: 2019/11/19 19:54:57 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_calc_tkn  *calc_get_inc_tkn(char *str, size_t pos)
{
    t_calc_tkn      *token;
    t_calc_tkntype  type;

    if (!str)
        return (NULL);
    type = (*str == '+') ? CALC_INC : CALC_DEC;
    if (!(token = calc_newtkn(NULL, type)))
        return (NULL);
    token->start_pos = pos;
    token->end_pos = pos + 2;
    return (token);
}