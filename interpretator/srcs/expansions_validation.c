/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:05:14 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/13 21:17:20 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

int		isvalidparameter(char s)
{
	if (s == '_' || (s >= 'A' && s <= 'Z') || (s >= 'a' && s <= 'z') ||
		(s >= '0' && s <= '9'))
		return (1);
	return (0);
}

int		isvalidword(char s, char snext)
{
	if ((isvalidparameter(s)) || (s == '=' || s == '-' || s == '+' ||
		s == '?' || s == ' '))
	{
		if (s == '_')
		{
			if (snext && !(isvalidparameter(snext)))
				return (0);
		}
		return (1);
	}
	return (0);
}

void	*word_validation(char *s, int i)
{
	if (s[i + 1])
	{
		if (!(isvalidword(s[i], s[i + 1])))
			return (exp_error(s));
	}
	else
	{
		if (!isvalidword(s[i], 0))
			return (exp_error(s));
	}
	return ("ok");
}

void	*parameter_validation(char *s, int i)
{
	while (s[i] != '}' && s[i])
	{
		if (s[i] == ':' && s[i + 1] != '}' && i != 0)
		{
			i++;
			if ((s[i] == '=' || s[i] == '-' || s[i] == '+' || s[i] == '?'))
			{
				while (s[i] && s[i] != '}')
					i++;
			}
			while (s[i] != '}' && s[i] && s[i] != '$')
			{
				if (!(ft_strcmp(word_validation(s, i), "err")))
					return ("err");
				i++;
			}
		}
		else if (!(isvalidparameter(s[i])))
			return (exp_error(s));
		i++;
	}
	return ("ok");
}

void	*expansions_validation(char *s)
{
	int		i;
	int		paramlen;
	char	*tmp;
	char	*ret;

	i = 0;
	if (!(paramlen = check_bracket(s)))
		return (0);
	if (s[2] == '#' && (i = 3))
	{
		while (s[i] != '}' && s[i] && s[i] != '$')
		{
			if (!(ft_strcmp(word_validation(s, i), "err")))
				return ("err");
			i++;
		}
		tmp = ft_strsub(s, 3, paramlen - 2);
		ret = ft_itoa(ft_strlen(get_var(tmp, ALL_VARS)));
		free(tmp);
		g_f = 1;
		return (ret);
	}
	if (!(ft_strcmp(parameter_validation(s, 2), "err")))
		return ("err");
	return (exp_implement(s + 2));
}
