/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/21 21:04:35 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		main(int argc, char **argv, char **environ)
{
	(void)argv;
	init_global_var(environ);
	if (argc == 1)
		term_start();
	free_globar_var();
	return (EXIT_SUCCESS);
}

void	term_start(void)
{
	char	*line;
	t_lex_tkn **tokens;

	signalling();
	init_readline();
	while (RUNNING)
	{
		if (!(line = ft_readline(get_env("PS1", ALL_ENV))))
			continue ;
		if (!ft_strcmp(line, "exit"))
			break ;
		tokens = lex_get_tkns(&line);
		lex_print_tkns(tokens);
		//ft_system(line);
		add_to_history_buff(line);
		ft_memdel((void**)&line);
	}
	free_readline();
}

void	ft_system(char *buffer)
{
	t_lex_tkn	**tokens;
	t_ast		*root;

	tokens = lex_get_tkns(&buffer);
	if (!tokens || !*tokens || (*tokens)->type == T_END)
	{
		lex_del_tkns(tokens);
		return ;
	}
	if (!make_ast(tokens, &root))
	{
		parse(root);
		exec_jobs(g_first_job);
	}
	ft_free_jobs(g_first_job);
	g_first_job = NULL;
	clean_tree(root);
	lex_del_tkns(tokens);
}
