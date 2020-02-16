/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaping_characters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 12:55:31 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/16 13:50:52 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static int esc_simple_chars(char *str, size_t *pos)
{
    if (str[*pos + 1] == 'a' || str[*pos + 1] == 'b' || str[*pos + 1] == 'e'
        || str[*pos + 1] == 'E' || str[*pos + 1] == 'f' || str[*pos + 1] == 'n'
        || str[*pos + 1] == 'r' || str[*pos + 1] == 't' || str[*pos + 1] == 'v')
    {
        (*pos) += 2;
        return (1);
    }
    return (0);
}

int esc_chars(char *str, size_t *pos)
{
    if (esc_simple_chars(str, pos))
        return (1);
    return (0);
}