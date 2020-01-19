/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_dar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 23:03:23 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/19 13:45:23 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static short	get_counter_env_dar(char *arr, char **env)
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

static char		**ft_getenv_names_dar(char *name, char **arr)
{
	int		size;
	char	**res;
	short	len;
	short	i;
	short	j;

	size = get_counter_env_dar(name, arr);
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

char			**get_env_names_dar(char *name, t_env mode)
{
	if (mode == ENV)
		return (ft_getenv_names_dar(name, g_env.env));
	else if (mode == SET_ENV)
		return (ft_getenv_names_dar(name, g_set_env.env));
	return (ft_darjoin(ft_getenv_names_dar(name, g_set_env.env),
						ft_getenv_names_dar(name, g_env.env)));
}
