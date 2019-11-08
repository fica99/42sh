/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/08 21:07:07 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		main(int argc, char **argv, char **environ)
{
	ft_putstr("*-------------------------------------------------------*\n");
	ft_putstr("│                                                       │\n");
	ft_putstr("|\033[0;31m");
	ft_putstr("             Say hello to my little friend!!!          ");
	ft_putstr("\033[0m|\n");
	ft_putstr("|                                                       │\n");
	ft_putstr("*-------------------------------------------------------*\n");
	init_global_var(argv, environ);
	if (argc == 1)
		term_start();
	free_globar_var();
	ft_putstr("*-------------------------------------------------------*\n");
	ft_putstr("│                                                       │\n");
	ft_putstr("|\033[0;35m");
	ft_putstr("              Goodbye my love, goodbye!!!              ");
	ft_putstr("\033[0m|\n");
	ft_putstr("|                                                       │\n");
	ft_putstr("*-------------------------------------------------------*\n");
	return (EXIT_SUCCESS);
}

void	term_start(void)
{
	char	*line;
	char	*prompt;

	prompt = "\033[0;36m\\u\033[0;31m@\033[0;32m\\H\033[0;31m:\033[0;33m\\w\n\033[0;35m\\$> \033[0m";
	init_readline(g_env.env);
	while (RUNNING)
	{
		g_flags = INIT_FLAGS;
		line = ft_readline(prompt, READLINE, g_env.env);
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
