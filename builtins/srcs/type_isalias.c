/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_isalias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 16:29:14 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/11 16:29:16 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int isalias(char *al)
{
    char *tmp;
    char *eq;

    if (!(tmp = ft_getalias(al, g_aliases.vars)))
        return (0);
    tmp = ft_strdup(tmp);
    eq = ft_strchr(tmp, '=');
    *eq = 0;
    eq++;
    ft_putstr(tmp);
    ft_putstr(" is an alias for ");
    ft_putstr(eq);
    ft_putstr("\n");
    free(tmp);
    return (1);
}