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
	char	*var;
	char	*spec;
	char	*copy;

	spec = ft_strchr(args, '$');
	var = ft_strnew(LINE_MAX);
	copy = NULL;
	if (spec != args)
		copy = ft_strsub(args, 0, spec - args);
	ft_strcat(var, copy);
	dollar_circle(spec, &var);
	ft_memdel((void**)&copy);
	ft_memdel((void**)&args);
	return (var);
}
