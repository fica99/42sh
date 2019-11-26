/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_num_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 19:48:32 by ggrimes           #+#    #+#             */
/*   Updated: 2019/11/26 21:22:15 by ggrimes          ###   ########.fr       */
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