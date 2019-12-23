/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:46:37 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/06 13:36:19 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

short	get_count_env(char *arr, char **env)
{
	short	i;
	short	len;

	if (arr && *arr)
	{
		i = -1;
		len = ft_strlen(arr);
		while (env[++i])
			if (!ft_strncmp(env[i], arr, len) && env[i][len] == '=')
				return (i);
	}
	return (-1);
}

void	ft_setenv(char *name, char *new_value, t_environ *env)
{
	short	j;
	char	**envp;

	if ((j = get_count_env(name, env->env)) >= 0)
	{
		ft_memdel((void**)&env->env[j]);
		env->env[j] = join_env(name, new_value);
	}
	else
	{
		if (++env->cur_size >= env->malloc_size)
		{
			env->malloc_size += DEFAULT_ENV_MALLOC_SIZE;
			if (!(envp = ft_darnew(env->malloc_size)))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
			j = -1;
			while (env->env[++j])
				envp[j] = env->env[j];
			envp[j] = join_env(name, new_value);
			ft_free_dar(env->env);
			env->env = envp;
		}
		else
			env->env[env->cur_size - 1] = join_env(name, new_value);
	}
}

char	*join_env(char *name, char *new_value)
{
	char *name1;
	char *name2;

	if (!(name1 = ft_strjoin(name, "=")))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	if (!new_value)
		return (name1);
	if (!(name2 = ft_strjoin(name1, new_value)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	ft_memdel((void**)&name1);
	return (name2);
}

void	ft_unsetenv(char *arr, t_environ *env)
{
	int		j;
	char	*copy;

	if ((j = get_count_env(arr, env->env)) < 0)
		return ;
	copy = env->env[j];
	while (j < env->cur_size)
	{
		env->env[j] = env->env[j + 1];
		j++;
	}
	--env->cur_size;
	ft_memdel((void**)&copy);
}

void	unset_env(char *name, t_env mode)
{
	if (mode == ENV)
		ft_unsetenv(name, &g_env);
	else if (mode == SET_ENV)
		ft_unsetenv(name, &g_set_env);
	else if (mode == ALL_ENV)
	{
		ft_unsetenv(name, &g_env);
		ft_unsetenv(name, &g_set_env);
	}
}
