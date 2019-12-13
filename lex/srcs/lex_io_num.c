/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_io_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:13:30 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/12 22:02:38 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int				lex_is_ionum(char *str, short is_word, size_t *pos)
{
	size_t	i;

	if (!str)
		return (0);
	i = *pos;
	if (i - 1 < i && str[i - 1] == '-')
		return (0);
	if (ft_isdigit(str[i]))
		i++;
	if (!(str[i] == '<' || str[i] == '>'))
		return (0);
	if (!is_word)
		(*pos) = i;
	return (1);
}

t_lex_tkn_type	lex_ionum(short is_word)
{
	if (is_word)
		return (T_NULL);
	return (T_IO_NUMBER);
}
