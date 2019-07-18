/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/07/18 12:36:42 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		main(int argc, char **argv, char **environ)
{
	t_term	term;

	(void)argv;
	if (!(g_env = ft_dardup(environ)))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	init_term();
	save_attr(&g_orig_mode);
	init_hash_table(&term);
	make_history_buff(&(term.history));
	if (argc == 1)
		term_start(&term);
	free_my_hash_table(term.hash_table, &term.hash_table_size);
	term.hash_table = NULL;
	free_history(&(term.history));
	ft_free_dar(g_env);
	return (EXIT_SUCCESS);
}

void	term_start(t_term *term)
{
	term->buffer = NULL;
	term->copy_line = NULL;
	while (RUNNING)
	{
		g_flags = INIT_FLAGS;
		signal(SIGWINCH, signal_handler);
		term_prompt();
		read_prompt(term);
		if (!(g_flags & TERM_EXIT) && !(g_flags & TERM_SIGINT) && term->buffer)
			parse_string(term);
		if (g_flags & TERM_INIT_HASH)
			init_hash_table(term);
		if (g_flags & TERM_FREE_HASH)
		{
			free_my_hash_table(term->hash_table, &term->hash_table_size);
			term->hash_table = NULL;
		}
		ft_memdel((void**)&term->buffer);
		if (g_flags & TERM_EXIT)
			break ;
	}
	ft_memdel((void**)&term->copy_line);
}

void	init_term(void)
{
	char	*term;
	int		err;

	if ((term = ft_getenv("TERM")) == NULL ||
	(setupterm(term, STDIN_FILENO, &err) == ERR))
		print_error("42sh", "setupterm() error", NULL, 0);
}
