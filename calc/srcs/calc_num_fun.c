/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_num_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 19:48:32 by ggrimes           #+#    #+#             */
/*   Updated: 2019/11/29 19:38:58 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_calc_tkn  *calc_get_number_tkn(char *str, size_t pos)
{
    size_t      i;
    char        *value;
    t_calc_tkn  *token;

    if (!str)
        return (NULL);
    i = 0;
    while (ft_isdigit(str[i]))
        i++;
    if (!(value = ft_strsub(str, 0, i)))
        return (NULL);
    if (!(token = calc_newtkn((void *)value, CALC_NUMBER)))
    {
        ft_memdel((void **)&value);
        return (NULL);
    }
    token->start_pos = pos;
    token->end_pos = pos + i;
    return (token);
}

int        calc_number(t_calc_tkn *token)
{
    char    *value;

    if (!token)
        return (0);
    if (token->type == CALC_NUMBER)
    {
        value = token->value;
        calc_del_tkn(&token);
        return (ft_atoi(value));
    }
    calc_del_tkn(&token);
    return (0);
}

int     calc_unary(char *str, t_calc_tkn *token, size_t *pos)
{
    if (!token || !str || !pos)
        return (0);
    if (token->type == CALC_MINUS)
    {
        *pos = token->end_pos;
        calc_del_tkn(&token);
        token = calc_get_next_tkn(str, *pos, NULL);
        return (calc_number(token) * -1);
    }
    else
        return (calc_number(token));
}