/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:57:34 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/22 19:12:42 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	init_global_var(char **argv, char **environ)
{
	if (!(g_argv = ft_dardup(argv)))
		err_exit(argv[0], "malloc() error", NULL, ENOMEM);
	init_global_env(&g_env, environ);
	init_bin_table(&g_bin_table);
	if (!(g_lexer = load_lexer()))
		err_exit(g_argv[0], "Error load lexor matrix", LEXER_MATRIX_PATH, NOERROR);
}

void	free_globar_var(void)
{
	free_bin_table(&g_bin_table);
	clear_lexer(&g_lexer);
	unset_env_struct(&g_env);
	ft_free_dar(g_argv);
}
