/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/29 23:04:03 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term.h"

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

	init_readline();
	g_last_job = NULL;
	init_jobs();
	while (RUNNING)
	{
		if (!(line = ft_readline(get_env("PS1", ALL_ENV))))
			continue ;
		ft_system(&line);
		add_to_history_buff(line);
		ft_memdel((void**)&line);
	}
	free_readline();
}

void	ft_system(char **buffer)
{
	t_lex_tkn	**tokens;
	t_ast		*root;

	tokens = lex_get_tkns(buffer);
	if (!tokens || !*tokens || (*tokens)->type == T_END)
	{
		lex_del_tkns(tokens);
		return ;
	}
	if (!make_ast(tokens, &root))
	{
		parse(root);
		exec_jobs();
	}
	clean_tree(root);
	lex_del_tkns(tokens);
}
