/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:57:34 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/21 22:35:16 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	init_global_var(char **argv, char **environ)
{
	init_global_env(&g_env, environ);
	init_bin_table(&g_bin_table);
	if (!(g_argv = ft_dardup(argv)))
		err_exit("malloc() error", NULL, ENOMEM);
	if (!(g_lexer = load_lexer()))
		err_exit("Error load lexor matrix", LEXER_MATRIX_PATH, NOERROR);
}

void	free_globar_var(void)
{
	free_bin_table(&g_bin_table);
	clear_lexer(&g_lexer);
	ft_free_dar(g_argv);
	unset_env_struct(&g_env);
}
