/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:57:34 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/01 11:39:43 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	init_global_var(char **argv, char **environ)
{
	g_argv = argv;
	init_global_env(&g_env, environ);
	init_bin_table(&g_bin_table);
	init_curr_pwd();
	init_shell(argv, environ);
	if (!(g_lexer = load_lexer()))
		err_exit(g_argv[0], "Error load lexor matrix", LEXER_MATRIX_PATH,
		NOERROR);
}

void	free_globar_var(void)
{
	clear_lexer(&g_lexer);
	free_table(&g_bin_table);
	unset_env_struct(&g_env);
}
