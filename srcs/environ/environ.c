/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 21:11:37 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/20 21:51:28 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_environ	*init_env_struct(char **arr, short malloc_size)
{
	t_environ	*env;

	if (!(env = (t_environ *)malloc(sizeof(t_environ))))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	env->malloc_size = malloc_size;
	if (!(env->env = ft_dardup(arr)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	env->cur_size = ft_darlen(arr);
	return (env);
}

void		free_env_struct(t_environ **env)
{
	if (env && *env)
	{
		ft_free_dar((*env)->env);
		(*env)->cur_size = 0;
		(*env)->malloc_size = 0;
		ft_memdel((void**)env);
	}
}
