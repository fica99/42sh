/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 07:13:33 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/13 21:17:02 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

void	*expansions(char *s)
{
	return (expansions_cycle(s));
}

void	is_circle(int i, char *tmp, char *spec, char **var)
{
	int	t;

	t = 0;
	if (!(tmp = ft_strnew(LINE_MAX)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	while (spec[i] != '$' && spec[i])
	{
		tmp[t++] = spec[i++];
	}
	i--;
	ft_strcat(*var, tmp);
	free(tmp);
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
		while (spec[i] && isvalidparameter(spec[i]))
			i++;
		ft_strcat(*var, (get_var((tmp = ft_strsub(spec, j, i - j)), ALL_VARS)));
		free(tmp);
		if (spec[i] == '$' && (!(spec[i + 1])))
			ft_strcat(*var, "$");
		else if (spec[i] != '$' && spec[i])
		{
			is_circle(i, tmp, spec, var);
		}
	}
}

char	*dollar_expr(char *args)
{
	char	*var;
	char	*spec;
	char	*copy;
	int		i;

	i = 0;
	spec = ft_strchr(args, '$');
	if (!(var = ft_strnew(LINE_MAX)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	copy = NULL;
	if (spec[1] == '{')
	{
		free(var);
		return (isexpansion(args));
	}
	if (spec != args)
		copy = ft_strsub(args, 0, spec - args);
	ft_strcat(var, copy);
	dollar_circle(spec, &var);
	ft_memdel((void**)&copy);
	return (var);
}

void	tilda_expr(char **args)
{
	char	*path;
	char	*index;
	char	*tmp;

	if ((path = get_var("HOME", ALL_VARS)))
	{
		index = ft_strchr(*args, '~');
		if (!(tmp = ft_strjoin(path, index + 1)))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
		ft_strdel(args);
		*args = tmp;
	}
}
