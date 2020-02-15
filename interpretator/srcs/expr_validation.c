/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:22:07 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/15 22:21:55 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

int		isvalidparameter(char s)
{
	if (s == '_' || ft_isalnum(s) || s == '?')
		return (1);
	return (0);
}

void	exp_error(char *s)
{
	err("42sh", s, "bad substitution", NULL);
}

int		expansions_validation(char *line, int pos)
{
	pos += 2;
	if (line[pos] == '#')
		pos++;
	if (line[pos] == '?' && line[pos + 1] == '}')
		return (0);
	while (line[pos] != '}')
	{
		if (line[pos] == ':' && line[pos + 1] != '}')
		{
			pos++;
			if ((line[pos] == '=' || line[pos] == '-' || line[pos] == '+' ||
			line[pos] == '?'))
			{
				while (line[pos] && line[pos] != '}')
					pos++;
			}
		}
		else if (!(isvalidparameter(line[pos])))
			return (1);
		line++;
		if (!line[pos])
			return (1);
	}
	return (0);
}
