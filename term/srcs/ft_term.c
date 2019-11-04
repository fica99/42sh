/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/04 17:17:08 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		main(int argc, char **argv, char **environ)
{
	init_global_var(argv, environ);
	if (argc == 1)
		term_start();
	free_globar_var();
	return (EXIT_SUCCESS);
}

void	term_start(void)
{
	char	*line;

	init_readline(g_env.env);
	while (RUNNING)
	{
		g_flags = INIT_FLAGS;
		line = ft_readline(ft_getenv("PS1", g_env.env), VI, g_env.env);
		check_valid_string(line);
		ft_memdel((void**)&line);
		if (g_flags & TERM_EXIT)
			break ;
	}
	free_readline();
}

void	check_valid_string(char *buffer)
{
	t_node	*ast;

	if (buffer && *buffer)
	{
		ast = parser(buffer);
		if (!(g_parser_flags & PARSER_ERROR))
			interpret_ast(ast);
		if (g_flags & TERM_FREE_HASH || g_flags & TERM_INIT_HASH)
		{
			free_table(&g_bin_table);
			if (g_flags & TERM_INIT_HASH)
				init_bin_table(&g_bin_table);
		}
		free_ast(&ast);
	}
}
