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
	if (spec[1] == '{')
		if (!(expansions(args + 2))) // NEED TO GET_ENV HERE
			return (0);
	copy = NULL;
	var = ft_strnew(LINE_MAX);
	if (spec != args)
		copy = ft_strsub(args, 0, spec - args);
	if ((arr = ft_strchr(spec, ' ')))
	{
		*arr = '\0';
		arr++;
	}
	ft_strcat(var, copy);
	while ((ft_strchr(spec + i, '$')))
	{
		i++;
		j = i;
		while(spec[i] != '$' && spec[i])
			i++;
		if ((path = get_env(ft_strsub(spec, j, i - j), ALL_ENV)))
			ft_strcat(var, path);
	}
	ft_strcat(var, arr);
	ft_memdel((void**)&copy);
	ft_memdel((void**)&args);
	return (var);
}
