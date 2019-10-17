/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/17 16:39:57 by aashara-         ###   ########.fr       */
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
	char	*ps1;

	make_history_buff(&g_history);
	save_attr(&g_orig_mode);
	init_terminfo();
	init_line(&g_line);
	while (RUNNING)
	{
		g_flags = INIT_FLAGS;
		signal(SIGWINCH, win_handler);
		if (!(ps1 = ft_getenv("PS1")))
			standart_prompt();
		line = ft_readline(ps1);
		check_valid_string(line);
		if (g_flags & TERM_EXIT)
			break ;
	}
	free_line(&g_line);
	reset_shell_mode();
	set_attr(&g_orig_mode);
	free_history(&g_history);
}

void	check_valid_string(char *buffer)
{
	t_node	*ast;

	if (buffer && *buffer)
	{
		ast = parser(buffer);
		if (!(g_parser_flags & PARSER_ERROR))
			interpret_ast(ast);
		if (ast)
		{
			add_to_history_buff(buffer, &g_history);
			free_ast(&ast);
		}
		if (g_flags & TERM_FREE_HASH || g_flags & TERM_INIT_HASH)
		{
			free_table(&g_bin_table);
			if (g_flags & TERM_INIT_HASH)
				init_bin_table(&g_bin_table);
		}
	}
}
