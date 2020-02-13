/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_implementation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:27:24 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/13 20:15:12 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

char	*empty_var(char *s, int i, char *param, int j)
{
	char	*for_free;

	if (s[i] == '=')
	{
		set_var(param,
		(for_free = (ft_strsub(s, i + 1, j - (i + 1)))), ALL_VARS);
		free(for_free);
	}
	if (s[i] == '?')
	{
		err("42sh", param,
		for_free = (ft_strsub(s, i + 1, j - (i + 1))), NULL);
		free(param);
		free(for_free);
		return (NULL);
	}
	if (s[i] == '+')
	{
		free(param);
		return (NULL);
	}
	return ("ok");
}

char	*question_equal(char *param, char *s, int i, int j)
{
	char	*for_free;

	if (s[i] == '=')
	{
		set_var(param, (for_free = (ft_strsub(s, i + 1, j - (i + 1)))),
		ALL_VARS);
		free(for_free);
	}
	if (s[i] == '?')
	{
		err("42sh", param, for_free =
		(ft_strsub(s, i + 1, j - (i + 1))), NULL);
		free(for_free);
		free(param);
		return (NULL);
	}
	if (s[i] == '+')
	{
		free(param);
		return (NULL);
	}
	return ("ok");
}

char	*not_empty_var(char *s, char *param, int i, int j)
{
	if (s[i] == '+')
	{
		if (s[i + 1] == '}')
		{
			free(param);
			return ("");
		}
		free(param);
		g_f = 1;
		return (ft_strsub(s, i + 1, j - (i + 1)));
	}
	free(param);
	return ("value");
}

char	*all_opers(char *param, char *s, int i, int j)
{
	char *tmp;
	char *value;

	if ((value = (get_var(param, ALL_VARS))))
	{
		if (!*value)
		{
			if (ft_strcmp(empty_var(s, i, param, j), "ok"))
				return (NULL);
		}
		else
		{
			if (!(ft_strcmp(tmp = not_empty_var(s, param, i, j), "value")))
				return (value);
			return (tmp);
		}
	}
	else
	{
		if (ft_strcmp(question_equal(param, s, i, j), "ok"))
			return (NULL);
	}
	free(param);
	g_f = 1;
	return (ft_strsub(s, i + 1, j - (i + 1)));
}

char	*exp_implement(char *s)
{
	int		i;
	int		j;
	char	*param;
	char	*tmp;

	i = 0;
	j = 0;
	param = ft_strnew(LINE_MAX);
	while (s[j])
	{
		j++;
		if (s[j] == '}')
			break ;
	}
	while (s[i] != ':' && s[i] != '}' && (param[i] = s[i]))
		i++;
	if (s[++i] == '-' || s[i] == '=' || s[i] == '?' || s[i] == '+')
		return (all_opers(param, s, i, j));
	else
	{
		tmp = get_var(param, ALL_VARS);
		free(param);
		return (tmp);
	}
}
