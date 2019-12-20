/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/17 23:13:00 by ggrimes          ###   ########.fr       */
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
		line = ft_readline(get_env("PS1", ALL_ENV), EMACS);
		if (!ft_strcmp(line, "exit"))
			break ;
		//subshell_expr(line); /* TODO перенести в парсер #96. */
		//subgroups_expr(line); /* TODO перенести в парсер #99. */
		check_valid_string(line);
		add_to_history_buff(line);
		ft_memdel((void**)&line);
		if (g_flags & TERM_EXIT)
			break ;
	}
	free_readline();
}

void	check_valid_string(char *buffer)
{
	t_lex_tkn	**tokens;

	tokens = lex_get_tkns(&buffer);
	//lex_print_tkns(tokens);
	parse(tokens);
}
