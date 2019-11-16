/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_eq_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 20:10:48 by ggrimes           #+#    #+#             */
/*   Updated: 2019/11/19 20:21:09 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_calc_tkn  *calc_get_eq_tkn(char *str, size_t pos)
{
    t_calc_tkn      *token;
    t_calc_tkntype  type;

    if (!str)
        return (NULL);
    type = (*str == '=') ? CALC_EQ : CALC_DIFF;
    if (!(token = calc_newtkn(NULL, type)))
        return (NULL);
    token->start_pos = pos;
    token->end_pos = pos + 2;
    return (token);
}