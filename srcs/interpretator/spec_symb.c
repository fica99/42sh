/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_symb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 23:30:58 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/14 17:59:17 by aashara-         ###   ########.fr       */
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
	char	*path;
	char	*arr;
	char	*spec;
	char	*copy;

	spec = ft_strchr(args, '~');
	if ((path = ft_getenv("HOME")))
	{
		arr = args;
		if (!(copy = ft_strjoin(path, spec + 1)))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
		*spec = '\0';
		if (!(args = ft_strjoin(args, copy)))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
		ft_memdel((void**)&copy);
		ft_memdel((void**)&arr);
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
		arr = arr + 1;
	}
	var = ft_strnew(LINE_MAX);
	ft_strcat(var, copy);
	if ((path = ft_getenv(spec + 1)))
		ft_strcat(var, path);
	ft_strcat(var, arr);
	ft_memdel((void**)&copy);
	ft_memdel((void**)&args);
	return (var);
}
