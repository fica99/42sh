/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_var_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 20:47:31 by ggrimes           #+#    #+#             */
/*   Updated: 2019/11/21 22:02:48 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_calc_tkn  *calc_get_var_tkn(char *str, size_t pos, int var_id, t_variables *variables)
{
    t_calc_tkn      *token;
    t_calc_tkntype  type;
    int             *value;

    if (!str)
        return (NULL);
    type = (*str == '$') ? CALC_PREFIXVAR : CALC_VAR;
    pos = (*str == '$') ? ++pos : pos;
    str = (*str == '$') ? ++str : str;
    if (variables->data[var_id].type != VAR_INT)
        return (calc_newtkn((void *)ft_strdup("Lexer syntax error!"), CALC_ERROR)); 
    if (!(value = (int *)malloc(sizeof(int))))
        return (NULL);
    *value = var_id;
    if (!(token = calc_newtkn((void *)value, type)))
    {   
        free(value);
        return (NULL);
    }
    token->start_pos = pos;
    token->end_pos = pos + ft_strlen(variables->data[var_id].name);
    return (token);
}

int         calc_check_variables(char *str, t_variables *variables)
{
    size_t          i;
    t_variable      *data;
    size_t          len;

    if (!str || !variables)
        return (-1);
    i = 0;
    data = variables->data;
    str = (*str == '$') ? ++str : str;
    while(i < variables->size)
    {
        len = ft_strlen(data[i].name);
        if (!ft_strncmp(str, data[i].name, len))
            return (i);
        i++;
    }
    return (-1);
}