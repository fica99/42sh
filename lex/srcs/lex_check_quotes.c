/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 20:50:33 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/12 22:04:19 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int	lex_is_quote(char c)
{
	if (c == '"' || c == '`' || c == '\'')
		return (1);
	return (0);
}

int	lex_check_quotes(char *str, size_t *pos)
{
	size_t	i;

	if (!str || !pos)
		return (0);
	i = *pos + 1;
	while (str[i] && !lex_is_quote(str[i]))
		i++;
	if (!str[i])
		return (0);
	(*pos) = i;
	return (1);
}
