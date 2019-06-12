/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:17:04 by filip             #+#    #+#             */
/*   Updated: 2019/06/12 22:30:57 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*ft_getenv(char *arr)
{
	if (get_count_var(arr) == -1)
		return (NULL);
	else
		return (g_term.env_cp[get_count_var(arr)] + ft_strlen(arr) + 1);
}

short	get_count_var(char *arr)
{
	short	i;

	i = -1;
	while (g_term.env_cp[++i])
	{
		if (ft_strncmp(g_term.env_cp[i], arr, ft_strlen(arr)) == 0
				&& g_term.env_cp[i][ft_strlen(arr)] == '=')
			return (i);
	}
	return (-1);
}

void	ft_setenv(char *name, char *new_value)
{
	short	j;
	char	**envp;

	if ((j = get_count_var(name)) >= 0)
	{
		free(g_term.env_cp[j]);
		g_term.env_cp[j] = join_env(name, new_value);
	}
	else
	{
		if (!(envp = (char**)malloc(sizeof(char*) *
						(double_arr_len(g_term.env_cp) + 2))))
			print_error("minishell", "malloc() error", NULL, ENOMEM);
		while (g_term.env_cp[++j])
			envp[j] = g_term.env_cp[j];
		envp[j] = join_env(name, new_value);
		envp[++j] = NULL;
		free(g_term.env_cp);
		g_term.env_cp = envp;
	}
}

char	*join_env(char *name, char *new_value)
{
	char *name1;
	char *name2;

	if (!(name1 = ft_strjoin(name, "=")))
		print_error("setenv", "malloc() error", NULL, ENOMEM);
	if (!(name2 = ft_strjoin(name1, new_value)))
		print_error("setenv", "malloc() error", NULL, ENOMEM);
	ft_memdel((void**)&name1);
	return (name2);
}

void	print_environ(void)
{
	short	i;

	i = -1;
	while (g_term.env_cp[++i])
	{
		ft_putstr_fd(g_term.env_cp[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}
