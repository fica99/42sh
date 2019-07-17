/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/07/18 01:39:44 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		main(int argc, char **argv, char **environ)
{
	t_term	term;

	(void)argc;
	(void)argv;
	if (!(g_env = ft_dardup(environ)))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	init_term();
	save_attr(&g_orig_mode);
	init_hash_table(&term);
	make_history_buff(&(term.history));
	term.buffer = NULL;
	term.copy_line = NULL;
	term_start(&term);
	ft_memdel((void**)&term.copy_line);
	free_my_hash_table(term.hash_table, &term.hash_table_size);
	term.hash_table = NULL;
	free_history(&(term.history));
	ft_free_dar(g_env);
	return (EXIT_SUCCESS);
}

void	term_start(t_term *term)
{
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
}

void	term_prompt(void)
{
	if (ft_getenv("PS1"))
		ft_putstr_fd(ft_getenv("PS1"), STDIN_FILENO);
	else
		standart_prompt();
}

void	standart_prompt(void)
{
	char	hostname[FT_HOST_NAME_MAX];

	gethostname(hostname, FT_HOST_NAME_MAX);
	RED(STDIN_FILENO);
	ft_putchar_fd('[', STDERR_FILENO);
	if (ft_getenv("USER"))
	{
		CYAN(STDIN_FILENO);
		ft_putstr_fd(ft_getenv("USER"), STDIN_FILENO);
		RED(STDIN_FILENO);
		ft_putchar_fd('@', STDIN_FILENO);
	}
	GREEN(STDIN_FILENO);
	ft_putstr_fd(hostname, STDIN_FILENO);
	if ((check_path()))
	{
		ft_putchar_fd(' ', STDIN_FILENO);
		YELLOW(STDIN_FILENO);
		ft_putstr_fd(check_path(), STDIN_FILENO);
	}
	RED(STDIN_FILENO);
	ft_putchar_fd(']', STDIN_FILENO);
	PURPLE(STDIN_FILENO);
	ft_putstr_fd(" $> ", STDIN_FILENO);
	STANDART(STDIN_FILENO);
}

void	init_term(void)
{
	char	*term;
	int		err;

	if ((term = ft_getenv("TERM")) == NULL ||
	(setupterm(term, STDIN_FILENO, &err) == ERR))
		print_error("42sh", "setupterm() error", NULL, 0);
}
