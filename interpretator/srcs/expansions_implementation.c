/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_implementation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 18:59:29 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/15 22:24:35 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static char	*e_strchr(const char *str, int ch)
{
	char	*pointer;
	int		i;

	i = 0;
	pointer = (char*)str;
	while (pointer[i] != '\0' && pointer[i] != '}')
	{
		if (pointer[i] == ch)
			return (&pointer[i]);
		i++;
	}
	return (NULL);
}

static char	*get_param(char *line, int pos)
{
	char *delim;

	pos += 2;
	if (line[pos] == '#')
		pos++;
	if (!(delim = e_strchr(&line[pos], ':')))
		delim = ft_strchr(&line[pos], '}');
	return (ft_strsub(&line[pos], 0, delim - &line[pos]));
}

static char	*simple_exp(char *line, int pos, char *param)
{
	line = strcutcopy(line, get_var(param, ALL_VARS), pos,
	ft_strlen(param) + 2);
	return (line);
}

char		*expansions(char *line, int pos)
{
	char	*param;
	char	*res;

	if (expansions_validation(line, pos))
	{
		exp_error(line + pos);
		return (NULL);
	}
	param = get_param(line, pos);
	res = simple_exp(line, pos, param);
	free(param);
	return (res);
}
