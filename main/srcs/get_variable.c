/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 18:04:37 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/06 16:56:24 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"

static short	get_count_vars(char *arr, char **env)
{
	short	i;
	short	len;
	short	counter;

	counter = 0;
	if (arr)
	{
		i = -1;
		len = ft_strlen(arr);
		while (env[++i])
			if (!ft_strncmp(env[i], arr, len))
				++counter;
	}
	return (counter);
}

static char		**ft_get_vars_names_dar(char *name, char **arr)
{
	int		size;
	char	**res;
	short	len;
	short	i;
	short	j;

	size = get_count_vars(name, arr);
	if (!(res = ft_darnew(size)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	i = -1;
	j = -1;
	len = ft_strlen(name);
	while (arr[++i])
	{
		if (!ft_strncmp(arr[i], name, len))
		{
			if (!(res[++j] = ft_strnew(ft_strchr(arr[i], '=') - arr[i] + 1)))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
			ft_strncat(ft_strcpy(res[j], "$"), arr[i], ft_strchr(arr[i], '=')
																	- arr[i]);
		}
	}
	return (res);
}

char			**get_vars_names_dar(char *name, t_vars_type type)
{
	if (type == ENV)
		return (ft_get_vars_names_dar(name, g_environ.vars));
	else if (type == VARS)
		return (ft_get_vars_names_dar(name, g_vars.vars));
	return (ft_darjoin(ft_get_vars_names_dar(name, g_vars.vars),
						ft_get_vars_names_dar(name, g_vars.vars)));
}

char			*ft_getvar(char *name, char **varlist)
{
	char	*tmp;
	long	varlen;

	if (!name || !*name)
		return (NULL);
	while (*varlist)
	{
		tmp = ft_strchr(*varlist, '=');
		varlen = tmp - *varlist;
		if ((long)ft_strlen(name) == varlen &&
		!ft_strncmp(name, *varlist, varlen))
			return (tmp + 1);
		++varlist;
	}
	return (NULL);
}

char			*get_var(char *arr, t_vars_type mode)
{
	char	*env;

	env = NULL;
	if (mode == ENV)
		return (ft_getvar(arr, g_environ.vars));
	else if (mode == VARS)
		return (ft_getvar(arr, g_vars.vars));
	if (!(env = ft_getvar(arr, g_vars.vars)))
		return (ft_getvar(arr, g_environ.vars));
	return (env);
}
