/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:46:37 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/16 13:55:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*ft_getenv(char *arr)
{
	short	j;
	char	**env;

	if (arr && *arr)
	{
		env = g_env.env;
		if ((j = get_count_env(arr)) != -1)
			return (ft_strchr(env[j], '=') + 1);
	}
	return (NULL);
}

short	get_count_env(char *arr)
{
	short	i;
	char	**env;
	short	len;

	if (arr && *arr)
	{
		i = -1;
		env = g_env.env;
		len = ft_strlen(arr);
		while (env[++i])
			if (!ft_strncmp(env[i], arr, len))
				return (i);
	}
	return (-1);
}

void	ft_setenv(char *name, char *new_value)
{
	short	j;
	char	**envp;

	if ((j = get_count_env(name)) >= 0)
	{
		free(g_env.env[j]);
		g_env.env[j] = join_env(name, new_value);
	}
	else
	{
		if (++g_env.cur_size >= g_env.malloc_size)
		{
			g_env.malloc_size += DEFAULT_ENV_MALLOC_SIZE;
			if (!(envp = ft_darnew(g_env.malloc_size)))
				err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
			j = -1;
			while (g_env.env[++j])
				envp[j] = g_env.env[j];
			envp[j] = join_env(name, new_value);
			ft_free_dar(g_env.env);
			g_env.env = envp;
		}
		else
			g_env.env[g_env.cur_size - 1] = join_env(name, new_value);
	}
}

char	*join_env(char *name, char *new_value)
{
	char *name1;
	char *name2;

	if (!(name1 = ft_strjoin(name, "=")))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	if (!(name2 = ft_strjoin(name1, new_value)))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	ft_memdel((void**)&name1);
	return (name2);
}

void	ft_unsetenv(char *arr)
{
	int		j;
	char	*copy;

	if ((j = get_count_env(arr)) < 0)
		return ;
	copy = g_env.env[j];
	while (j < g_env.cur_size)
	{
		g_env.env[j] = g_env.env[j + 1];
		j++;
	}
	g_env.cur_size--;
	ft_memdel((void**)&copy);
}
