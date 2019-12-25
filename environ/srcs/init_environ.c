/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 21:11:37 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/21 16:13:24 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		init_global_env(t_environ *env, char **arr)
{
	int		len;
	int		counter;

	len = ft_darlen(arr);
	counter = 1;
	while (len >= counter * DEFAULT_ENV_MALLOC_SIZE)
		counter++;
	set_env_struct(env, arr, counter * DEFAULT_ENV_MALLOC_SIZE);
}

void		set_env_struct(t_environ *env, char **arr, short malloc_size)
{
	int		i;

	env->malloc_size = malloc_size;
	if (!(env->env = ft_darnew(malloc_size)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	i = -1;
	while (arr[++i])
		if (!(env->env[i] = ft_strdup(arr[i])))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
	env->cur_size = i;
}

void		unset_env_struct(t_environ *env)
{
	if (env)
	{
		ft_free_dar((env)->env);
		(env)->cur_size = 0;
		(env)->malloc_size = 0;
	}
}

char		*get_env(char *arr, t_env mode)
{
	char	*env;

	if (mode == ENV)
		return (ft_getenv(arr, g_env.env));
	else if (mode == SET_ENV)
		return (ft_getenv(arr, g_set_env.env));
	if (!(env = ft_getenv(arr, g_env.env)))
		return (ft_getenv(arr, g_set_env.env));
	return (env);
}

void		set_env(char *name, char *new_value, t_env mode)
{
	if (mode == ENV)
		ft_setenv(name, new_value, &g_env);
	else if (mode == SET_ENV)
		ft_setenv(name, new_value, &g_set_env);
	else
	{
		if (ft_getenv(name, g_env.env))
			ft_setenv(name, new_value, &g_env);
		else
			ft_setenv(name, new_value, &g_set_env);
	}
}
