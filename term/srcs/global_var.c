/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:57:34 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/08 19:48:10 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	init_global_var(char **environ)
{
	char	*values[1];

	values[0] = NULL;
	init_global_env(&g_env, environ);
	init_global_env(&g_set_env, values);
	init_bin_table(&g_bin_table);
	init_built_table(&g_built_table);
	init_curr_pwd();
	set_env("?", "0", ALL_ENV);
}

void	free_globar_var(void)
{
	free(g_curr_dir);
	free_table(&g_bin_table);
	unset_env_struct(&g_set_env);
	unset_env_struct(&g_env);
}
