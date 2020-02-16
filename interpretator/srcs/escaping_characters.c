/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaping_characters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 12:55:31 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/16 14:19:50 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static int	esc_simple_chars(char *str, size_t *pos, short is_rep_pos)
{
	if (str[*pos + 1] == 'a' || str[*pos + 1] == 'b' || str[*pos + 1] == 'e'
		|| str[*pos + 1] == 'E' || str[*pos + 1] == 'f' || str[*pos + 1] == 'n'
		|| str[*pos + 1] == 'r' || str[*pos + 1] == 't' || str[*pos + 1] == 'v')
	{
		if (is_rep_pos)
			(*pos) += 2;
		return (1);
	}
	return (0);
}

static int	esc_hex_num(char *str, size_t *pos, short is_rep_pos)
{
	size_t	new_pos;
	size_t	i;

	new_pos = (*pos) + 1;
	if (str[new_pos++] != 'x')
		return (0);
	if (!ft_isdigit(str[new_pos]))
		return (0);
	i = 0;
	while (ft_isdigit(str[new_pos + i]) || ft_isupper(str[new_pos + i]))
		i++;
	if (i != 2)
		return (0);
	if (is_rep_pos)
		(*pos) = new_pos + i;
	return (1);
}

int			esc_chars(char *str, size_t *pos)
{
	if (esc_simple_chars(str, pos, 1))
		return (1);
	if (esc_hex_num(str, pos, 1))
		return (1);
	return (0);
}
