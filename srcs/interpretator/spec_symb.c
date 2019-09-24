/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_symb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 23:30:58 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/24 15:48:11 by aashara-         ###   ########.fr       */
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
	int		index;

	if ((path = ft_getenv("HOME")))
	{
		index = ft_strchr(args, '~') - args;
		args = ft_strdel_el(args, index);
		args = ft_stradd(args, path, index);
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
	if ((path = ft_getenv(spec + 1)))
		ft_strcat(var, path);
	ft_strcat(var, arr);
	ft_memdel((void**)&copy);
	ft_memdel((void**)&args);
	return (var);
}
