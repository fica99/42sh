/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:57:34 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/06 13:36:19 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	init_global_var(char **environ)
{
	char	*values[7];

	values[0] = "HISTFILE=";
	values[1] = "HISTFILESIZE=";
	values[2] = "HISTSIZE=";
	values[3] = "PS1=";
	values[4] = "PS2=";
	values[5] = "PS4=";
	values[6] = NULL;
	init_global_env(&g_env, environ);
	init_global_env(&g_set_env, values);
	init_bin_table(&g_bin_table);
	init_curr_pwd();
	if (!(g_lexer = load_lexer()))
		err_exit("42sh", "Error load lexor matrix", LEXER_MATRIX_PATH,
		NOERROR);
}

void	free_globar_var(void)
{
	clear_lexer(&g_lexer);
	free_table(&g_bin_table);
	unset_env_struct(&g_set_env);
	unset_env_struct(&g_env);
}
