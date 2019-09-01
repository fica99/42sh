/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/31 17:08:41 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		main(int argc, char **argv, char **environ)
{
	t_term	term;

	save_attr(&g_orig_mode);
	if (!(g_env = ft_dardup(environ)))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	if (!(g_argv = ft_dardup(argv)))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	term.hash_table = init_hash_table(&term.hash_table_size);
	if (argc == 1)
	{
		init_term();
		make_history_buff(&(term.history));
		term.buffer = NULL;
		term.copy_line = NULL;
		term_start(&term);
		free_history(&(term.history));
	}
	free_my_hash_table(term.hash_table, &term.hash_table_size);
	term.hash_table = NULL;
	ft_free_dar(g_argv);
	ft_free_dar(g_env);
	return (EXIT_SUCCESS);
}

void	term_start(t_term *term)
{
	t_node	*ast;

	while (RUNNING)
	{
		g_flags = INIT_FLAGS;
		signal(SIGWINCH, win_handler);
		term_prompt(ft_darlen(term->history.history_buff), g_argv[0]);
		read_prompt(term);
		if (!(g_flags & TERM_EXIT) && !(g_flags & TERM_SIGINT) && term->buffer)
		{
			ast = parser(term->buffer);
			interpret_ast(ast, term);
			free_ast(&ast);
		}
		if (g_flags & TERM_FREE_HASH || g_flags & TERM_INIT_HASH)
		{
			free_my_hash_table(term->hash_table, &term->hash_table_size);
			term->hash_table = NULL;
			if (g_flags & TERM_INIT_HASH)
				term->hash_table = init_hash_table(&term->hash_table_size);
		}
		ft_memdel((void**)&term->buffer);
		if (g_flags & TERM_EXIT)
			break ;
	}
	ft_memdel((void**)&term->copy_line);
}

void	init_term(void)
{
	int		err;

	if ((setupterm(0, STDIN_FILENO, &err) == ERR))
	{
		if (err == 1)
			print_error("42sh", "setupterm() error", EHRDCPY, 0);
		else if (err == 0)
			print_error("42sh", "setupterm() error", ENTFND, 0);
		else if (err == -1)
			print_error("42sh", "setupterm() error", ENOTERMINFO, 0);
	}
}
