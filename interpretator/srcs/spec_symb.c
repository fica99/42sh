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
		args = dollar_expr(args);
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

char	*dollar_expr(char *args)
{
	char	*arr;
	char	*var;
	char	*spec;
	char	*copy;
	char	*path;
	int		i;
	int		j;

	i = 0;
	spec = ft_strchr(args, '$');
	var = ft_strnew(LINE_MAX);
	copy = NULL;
	if (spec != args)              // 3 кейса - sdjsd${HOME}; sdsd${HOME}fdf; ${HOME}dfdf
		copy = ft_strsub(args, 0, spec - args);
	if ((arr = ft_strchr(spec, ' ')))
	{
		*arr = '\0';
		arr++;
	}
	ft_strcat(var, copy);
	if (spec[1] == '{')
	{
		var[0] = '$';
		if (ft_strcmp("$", (ft_strcat(var, (expansions(spec + 2))))) == 0)
			return (0);
	}
	if (!(spec[1] == '{'))
	{
		while ((ft_strchr(spec + i, '$')))
		{
			i++;
			j = i;
			while(spec[i] != '$' && spec[i])
				i++;
			if ((path = get_env(ft_strsub(spec, j, i - j), ALL_ENV)))
				ft_strcat(var, path);
		}
	}
	ft_strcat(var, arr);
	ft_memdel((void**)&copy);
	ft_memdel((void**)&args);
	return (var);
}
