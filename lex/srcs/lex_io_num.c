/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_io_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:13:30 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/10 22:42:14 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int	lex_is_ionum(char *str, short is_word, size_t *pos)
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
