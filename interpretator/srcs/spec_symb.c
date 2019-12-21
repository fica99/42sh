/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_symb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 23:30:58 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/07 12:21:13 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*spec_symbols(char *args)
{
	while (ft_strchr(args, '~'))
		args = tilda_expr(args);
	while (ft_strchr(args, '$'))
	{
		args = dollar_expr(args);
		if (args == NULL)
			break ;
	}
	return (args);
}

char	*tilda_expr(char *args)
{
	char	*tmp;
	char	*path;
	char	*index;

	tmp = args;
	if ((path = get_env("HOME", ALL_ENV)))
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
	int i;
	int j;

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
		if (!(path = expansions(spec + 2)))
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
				ft_strcat(var, path); // вместо path готовый expans.
			}
		}
		args += ((ft_strlen(copy1) + i) + 1);
	}
	return (var);
}

void	dollar_circle(char *spec, char **var)
{
	int		i;
	int		j;
	char	*tmp;
	
	i = 0;
	while ((ft_strchr(spec + i, '$')))
	{
		i++;
		j = i;
		while (spec[i] != '$' && spec[i])
			i++;
		ft_strcat(*var, (get_env((tmp = ft_strsub(spec, j, i - j)), ALL_ENV)));
		free(tmp);
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
	/*if (!copy)
		if (!(spec[1]))
			return (args);*/
	if ((arr = ft_strchr(spec, ' '))) // шо эта?
	{
		*arr = '\0';
		arr++;
	}
	ft_strcat(var, copy);
	dollar_circle(spec, &var);
	/*while ((ft_strchr(spec + i, '$')))
	{
		i++;
		j = i;
		while (spec[i] != '$' && spec[i])
			i++;
		ft_strcat(var, (get_env(ft_strsub(spec, j, i - j), ALL_ENV)));
	}*/
	ft_strcat(var, arr);
	ft_memdel((void**)&copy);
	ft_memdel((void**)&args);
	return (var);
}
