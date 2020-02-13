/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:05:14 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/13 05:45:27 by jijerde          ###   ########.fr       */
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

void	*expansions_validation(char *s)
{
	int		i;
	int		paramlen;
	char	*tmp;
	char	*ret;
	
	i = 0;
	if (!(paramlen = check_bracket(s)))
		return (0);
	if (s[2] == '#')
	{
		i++;
		while (s[i] != '}' && s[i] && s[i] != '$')
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
			i++;
		}
		ret = ft_itoa(ft_strlen(get_var(tmp = (ft_strsub(s, 3, paramlen - 2)), ALL_VARS)));
		free(tmp);
		g_f = 1;
		return (ret);
	}
	i = 2;
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
				i++;
			}
		}
		else if (!(isvalidparameter(s[i])))
			return (exp_error(s));
		i++;
	}
	return (exp_implement(s + 2));
}

void	*expansions(char *s)
{
	//if we see $ character, and the next is {, we go here with pointer
	//after {.
	/*int		i;
	//int		j;
	int		paramlen;
	//char	*repl;

	i = 0;*/
	/*if (!(paramlen = check_bracket(s)))
		return (0);
	if (s[2] == '#')
		return (ft_itoa(ft_strlen(get_var(ft_strsub(s, 1, paramlen), ALL_VARS))));*/
	return (expansions_cycle(s));
	/*while (s[i] != '}' && s[i] && s[i] != '$')
	{
		if (s[i] == ':' && s[i + 1] != '}' && i != 0)
		{
			i++;
			if ((s[i] == '=' || s[i] == '-' || s[i] == '+' || s[i] == '?'))
			{
				j = i;
				while (s[i] && s[i] != '$')
				i++;
			}
			while (s[i] != '}' && s[i] && s[i] != '$')
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
				i++;
			}
			if (s[i] == '$' && s[i + 1] != '}')
			{
				while (s[i] != '}')
					i++;
				repl = exp_implement(ft_strsub(s, j + 1, i - j));
				while (s[j])
				{
					s[]
				}
			}
		}
		else if (!(isvalidparameter(s[i])))
			return (exp_error(s));
		i++;
	}
	return (exp_implement(s));*/
}
