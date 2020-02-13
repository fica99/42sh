/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_symb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 23:30:58 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/13 18:06:39 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

int		final_in_cycle(char *spec, char *path, char **var, char *copy1)
{
	int i;

	i = 0;
	while (spec[i] != '}' && spec[i])
	{
		i++;
		while (spec[i] != '}' && spec[i])
			i++;
		if (path)
		{
			ft_strcat(*var, copy1);
			ft_strcat(*var, path);
			if (g_f == 1)
				free(path);
		}
	}
	while (spec[i] == '}' && spec[i])
		i++;
	i--;
	return (i);
}

void	*beg_of_cycle(char **spec, char *args, char **var, char **copy1)
{
	*spec = ft_strchr(args, '$');
	if (!*spec)
	{
		ft_strcat(*var, args);
		return (*var);
	}
	*copy1 = NULL;
	return ("no");
}

void	*exp_return(char *copy1, char *var, char **path, char *spec)
{
	if (!(*path = expansions(spec)))
	{
		if (copy1)
			free(copy1);
		free(var);
		return (NULL);
	}
	return (*path);
}

char	*isexpansion(char *args)
{
	char	*var;
	char	*spec;
	char	*copy1;
	char	*path;
	int		z;

	z = 0;
	spec = NULL;
	if (!(var = ft_strnew(LINE_MAX)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	while (args[z])
	{
		if (ft_strcmp(beg_of_cycle(&spec, args, &var, &copy1), "no"))
			return (var);
		if (spec != args)
			copy1 = ft_strsub(args, 0, spec - args);
		if (!(exp_return(copy1, var, &path, spec)))
			return (NULL);
		args += (z = ((ft_strlen(copy1) +
		final_in_cycle(spec, path, &var, copy1)) + 1));
		if (copy1)
			free(copy1);
	}
	ft_strcat(var, args);
	return (var);
}

char	*spec_symbols(char **args)
{
	char	*tmp;
	char	*dollar;
	int		i;

	i = 0;
	while (ft_strchr(*args, '~'))
		tilda_expr(args);
	while ((dollar = ft_strchr(*args, '$')) && (ft_strcmp(dollar, "$")))
	{
		tmp = dollar_expr(*args);
		if (i)
			free(*args);
		*args = tmp;
		i++;
		if (*args == NULL)
			break ;
	}
	return (*args);
}
