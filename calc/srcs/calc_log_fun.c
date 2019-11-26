/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_log_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 20:21:02 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/01 14:47:30 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_calc_tkn  *calc_get_log_tkn(char *str, size_t pos)
{
    t_calc_tkn      *token;
    t_calc_tkntype  type;

    if (!str)
        return (NULL);
    type = (*str == '&') ? CALC_AND : CALC_OR;
    if (!(token = calc_newtkn(NULL, type)))
        return (NULL);
    token->start_pos = pos;
    token->end_pos = pos + 2;
    return (token);
}