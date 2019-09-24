/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:57:34 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/25 18:06:26 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	init_global_var(char **argv, char **environ)
{
	save_attr(&g_orig_mode);
	g_argv = argv;
	init_global_env(&g_env, environ);
	init_bin_table(&g_bin_table);
	if (!(g_lexer = load_lexer()))
		err_exit(g_argv[0], "Error load lexor matrix", LEXER_MATRIX_PATH,
		NOERROR);
}

void	free_globar_var(void)
{
	clear_lexer(&g_lexer);
	free_table(&g_bin_table);
	unset_env_struct(&g_env);
	set_attr(&g_orig_mode);
}
