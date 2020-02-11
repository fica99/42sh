/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_implementation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:27:24 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/10 18:04:38 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

char *exp_implement(char *s)
{
	int		i;
	int		j;
	char	*param;
	char	*value;

	i = 0;
	j = 0;
	param = ft_strnew(LINE_MAX);
	//value = ft_strnew(LINE_MAX);
	while (s[j])
	{
		j++;
		if (s[j] == '}')
			break ;
	}
	while (s[i] != ':' && s[i] != '}')
	{
		param[i] = s[i];
		i++;
	}
	if (s[++i] == '-' || s[i] == '=' || s[i] == '?' || s[i] == '+')
	{
		if ((value = (get_var(param, ALL_VARS))))
		{
			if (!*value)
			{
				if (s[i] == '=')
					set_var(param, (ft_strsub(s, i + 1, j - (i + 1))), ALL_VARS);
				if (s[i] == '?')
				{
					err("42sh", param, ft_strsub(s, i + 1, j - (i + 1)), NULL);
					return (NULL);
				}
				if (s[i] == '+')
					return (NULL);
			}
			else
			{
				if (s[i] == '+')
					return (ft_strsub(s, i + 1, j - (i + 1)));
				return (value);
			}
		}
		else
		{
			if (s[i] == '=')
				set_var(param, (ft_strsub(s, i + 1, j - (i + 1))), ALL_VARS);
			if (s[i] == '?')
			{
				err("42sh", param, ft_strsub(s, i + 1, j - (i + 1)), NULL);
				return (NULL);
			}
			if (s[i] == '+')
				return (NULL);
		}
		return (ft_strsub(s, i + 1, j - (i + 1)));
	}
	else
		return (get_var(param, ALL_VARS));
}
