/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_symb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 23:30:58 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/12 00:07:50 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static char	*tilda_expr(char *args)
{
	char	*tmp;
	char	*path;
	char	*index;

	tmp = args;
	if ((path = get_var("HOME", ALL_VARS)))
	{
		index = ft_strchr(args, '~');
		args = ft_strjoin(path, index + 1);
		free(tmp);
	}
	return (args);
}

char	*isexpansion(char *args)
{
	char	*var;
	char	*spec;
	char	*copy1;
	char	*path;
	int		i;
	int		j;

	var = ft_strnew(LINE_MAX);
	path = ft_strnew(LINE_MAX);
	while (*args)
	{
		i = 1;
		j = 0;
		spec = ft_strchr(args, '$');
		if (!spec)
		{
			ft_strcat(var, args);
			return (var);
		}
		copy1 = NULL;
		if (spec != args)
			copy1 = ft_strsub(args, 0, spec - args);
		if (!(path = expansions(spec)))
			return (NULL); //invalid exp error here
		while (spec[i] != '}')
		{
			i++;
			j = i;
			while (spec[i] != '}')
				i++;
			if (path)
			{
				ft_strcat(var, copy1);
				ft_strcat(var, path);
			}
		}
		args += ((ft_strlen(copy1) + i) + 1);
	}
	return (var);
}

static void	dollar_circle(char *spec, char **var)
{
	int		i;
	int		j;
	int		t;
	char	*tmp;

	i = 0;
	while ((ft_strchr(spec + i, '$')))
	{
		i++;
		j = i;
		while (spec[i] && isvalidparameter(spec[i]))
			i++;
		ft_strcat(*var, (get_var((tmp = ft_strsub(spec, j, i - j)), ALL_VARS)));
		free(tmp);
		if (spec[i] == '$' && (!(spec[i + 1])))
			ft_strcat(*var, "$");
		else if (spec[i] != '$' && spec[i])
		{
			t = 0;
			tmp = ft_strnew(LINE_MAX);
			while (spec[i] != '$' && spec[i])
			{
				tmp[t++] = spec[i++];
			}
			i--;
			ft_strcat(*var, tmp);
			free(tmp);
		}
	}
}

char	*dollar_expr(char *args)
{
	char	*arr;
	char	*var;
	char	*spec;
	char	*copy;
	int		i;

	i = 0;
	spec = ft_strchr(args, '$');
	var = ft_strnew(LINE_MAX);
	copy = NULL;
	if (spec[1] == '{')
	{
		return (isexpansion(args));
	}
	if (spec != args)
		copy = ft_strsub(args, 0, spec - args);
	if ((arr = ft_strchr(spec, ' '))) // шо эта?
	{
		*arr = '\0';
		arr++;
	}
	ft_strcat(var, copy);
	dollar_circle(spec, &var);
	ft_strcat(var, arr);
	ft_memdel((void**)&copy);
	ft_memdel((void**)&args);
	return (var);
}

char	*spec_symbols(char *args)
{
	while (ft_strchr(args, '~'))
		args = tilda_expr(args);
	while (ft_strchr(args, '$') && (!(ft_strcmp((ft_strchr(args, '$')), "$") == 0)))
	{
		args = dollar_expr(args);
		if (args == NULL)
			break ;
	}
	return (args);
}
