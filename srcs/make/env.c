/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:17:04 by filip             #+#    #+#             */
/*   Updated: 2019/09/21 19:49:23 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"





void	ft_setenv(char *name, char *new_value)
{
	short	j;
	char	**envp;

	if ((j = get_count_var(name)) >= 0)
	{
		free(g_env[j]);
		g_env[j] = join_env(name, new_value);
	}
	else
	{
		if (!(envp = (char**)malloc(sizeof(char*) *
						(ft_darlen(g_env) + 2))))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
		while (g_env[++j])
			envp[j] = g_env[j];
		envp[j] = join_env(name, new_value);
		envp[++j] = NULL;
		free(g_env);
		g_env = envp;
	}
}

char	*join_env(char *name, char *new_value)
{
	char *name1;
	char *name2;

	if (!(name1 = ft_strjoin(name, "=")))
		err_exit("setenv", "malloc() error", NULL, ENOMEM);
	if (!(name2 = ft_strjoin(name1, new_value)))
		err_exit("setenv", "malloc() error", NULL, ENOMEM);
	ft_memdel((void**)&name1);
	return (name2);
}

void	print_environ(void)
{
	short	i;

	i = -1;
	while (g_env[++i])
	{
		ft_putstr_fd(g_env[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}
