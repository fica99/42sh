/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/01 22:27:11 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		main(int argc, char **argv, char **environ)
{
	(void)argv;

	ft_putstr("*-------------------------------------------------------*\n");
	ft_putstr("│                                                       │\n");
	ft_putstr("|\033[0;31m");
	ft_putstr("             Say hello to my little friend!!!          ");
	ft_putstr("\033[0m|\n");
	ft_putstr("|                                                       │\n");
	ft_putstr("*-------------------------------------------------------*\n");
	init_global_var(environ);
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

	init_readline();
	init_jobs();
	while (RUNNING)
	{
		g_flags = INIT_FLAGS;
		line = ft_readline(get_env("PS1", SET_ENV), VI);
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
		add_to_history_buff(buffer);
	}
}
