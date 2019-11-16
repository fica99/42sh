/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_com_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:24:35 by ggrimes           #+#    #+#             */
/*   Updated: 2019/11/19 20:00:55 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

static t_calc_tkntype  calc_com_type(char *str)
{
    if (!str)
        return (0);
    else if (!ft_strncmp(str, "<=", 2))
        return (CALC_LESSOREQ);
    else if (!ft_strncmp(str, ">=", 2))
        return (CALC_MOREOREQ);
    else if (*str == '<')
        return (CALC_LESS);
    else if (*str == '>')
        return (CALC_MORE);
    else
        return (0);            
}

t_calc_tkn  *calc_get_com_tkn(char *str, size_t pos)
{
    t_calc_tkn      *token;
    t_calc_tkntype  type;
    size_t          len;

    if (!str)
        return (NULL);
    len = (!ft_strncmp(str, "<=", 2) 
        || !ft_strncmp(str, ">=", 2)) ? 2 : 1;
    type = calc_com_type(str);
    if (!(token = calc_newtkn(NULL, type)))
        return (NULL);
    token->start_pos = pos;
    token->end_pos = pos + len;
    return (token);
}