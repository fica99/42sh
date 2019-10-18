/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 21:11:37 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/18 19:45:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_shell.h"


void		init_global_env(t_environ *env, char **arr)
{
	int	len;
	int	counter;

	len = ft_darlen(arr);
	counter = 1;
	while (len >= counter * DEFAULT_ENV_MALLOC_SIZE)
		counter++;
	set_env_struct(env, arr, counter * DEFAULT_ENV_MALLOC_SIZE);
}
void	set_env_struct(t_environ *env, char **arr, short malloc_size)
{
	int			i;

	env->malloc_size = malloc_size;
	if (!(env->env = ft_darnew(malloc_size)))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	i = -1;
	while (arr[++i])
		if (!(env->env[i] = ft_strdup(arr[i])))
			err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
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
