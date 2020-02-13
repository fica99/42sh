/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_implementation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:27:24 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/12 20:59:32 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

char *exp_implement(char *s)
{
	int		i;
	int		j;
	char	*param;
	char	*value;
	char	*tmp;

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
					free(param);
					return (NULL);
				}
				if (s[i] == '+')
				{
					free(param);
					return (NULL);
				}
			}
			else
			{
				if (s[i] == '+')
				{
					if (s[i + 1] == '}')
					{
						free(param);
						return ("");
					}
					free(param);
					return (ft_strsub(s, i + 1, j - (i + 1)));
				}
				free(param);
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
				free(param);
				return (NULL);
			}
			if (s[i] == '+')
			{
				free(param);
				return (NULL);
			}
		}
		free(param);
		return (ft_strsub(s, i + 1, j - (i + 1)));
	}
	else
	{
		tmp = get_var(param, ALL_VARS);
		free(param);
		return (tmp);
	}
}
