/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_symb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 23:30:58 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/01 11:20:18 by lcrawn           ###   ########.fr       */
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
	if ((path = get_env("HOME", ENV)))
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

	spec = ft_strchr(args, '$');
	arr = NULL;
	copy = NULL;
	if (spec != args)
		copy = ft_strsub(args, 0, spec - args);
	if ((arr = ft_strchr(spec, ' ')))
	{
		*arr = '\0';
		arr++;
	}
	var = ft_strnew(LINE_MAX);
	ft_strcat(var, copy);
	if ((path = get_env(spec + 1, ENV)))
		ft_strcat(var, path);
	ft_strcat(var, arr);
	ft_memdel((void**)&copy);
	ft_memdel((void**)&args);
	return (var);
}
