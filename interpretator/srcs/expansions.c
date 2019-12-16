/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:05:14 by jijerde           #+#    #+#             */
/*   Updated: 2019/12/11 18:20:00 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		isvalidword(char s)
{
	(void)s;
	return (0);
}

int		isvalidparameter(char s)
{
	if (s == '_' || (s >= 'A' && s <= 'Z') || (s >= 'a' && s <= 'z') ||
		(s >= '0' && s <= '9'))
		return (1);
	return (0);
}

int		check_bracket(char *s)
{
	int i;

	i = 0;
	if (s[i] == '}' || ((s[i] == '_' && s[i + 1] == '}')))
		return (0);
	while (s[i])
	{
		if (s[i] == '}')
		{
			if (i == 1)
				return (1);
			return (i - 1);
		}
		i++;
	}
	return (0);
}

void	*expansions(char *s)
{
	//if we see $ character, and the next is {, we go here with pointer
	//after {.
	int		i;
	int		paramlen;

	i = 0;
	if (!(paramlen = check_bracket(s)))
		return (0);
	if (s[i] == '#')
		return ((int *)ft_strlen(get_env(ft_strsub(s, 1, paramlen), ALL_ENV)));
	while (s[i] != '}' && s[i])
	{
		if (s[i] == ':' && s[i + 1] != '}')
		{
			while (s[i] && (isvalidword(s[i])))
				i++;
		}
		else if (!(isvalidparameter(s[i])))
		{
			ft_error("bash", s, "syntax error", "operand expected");
			return (0);
		}
		i++;
	}
	return (ft_strsub(s, 0, i));
}
