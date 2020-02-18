/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:41:23 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/19 01:41:18 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_shell(char **environ)
{
	init_variables(environ, ENV);
	init_variables(NULL, VARS);
	init_bin_hash_table();
	init_builtins_hash_table();
	set_variables(&g_aliases, NULL, VAR_DEF_MALLOC_SIZE);
	init_cwd();
	set_var("?", "0", VARS);
	if (!(get_var("PS1", ENV)))
		set_var("PS1",
		"\033[0;36m\\u \033[0;32m\\H \033[0;33m\\w\n\033[0m\\$> ", VARS);
	if (!(get_var("PS2", ENV)))
		set_var("PS2", "> ", VARS);
	set_var("READMODE", "EMACS", VARS);
	init_readline();
	init_jobs();
}

void		ft_system(char **line)
{
	t_lex_tkn	**tokens;
	t_ast		*root;

	tokens = lex_get_tkns(line);
	if (g_lex_stat != LS_OK)
	{
		err("42sh", "unexpected syntax error", NULL, NOERROR);
		g_last_exit_status = 1;
		set_var("?", "1", ALL_VARS);
		return ;
	}
	tokens = alias_handle(tokens);
	if (tokens && *tokens && (*tokens)->type != T_END)
	{
		root = NULL;
		if (!make_ast(tokens, &root))
		{
			parse(root);
			exec_jobs();
		}
		clean_tree(root);
	}
	lex_del_tkns(tokens);
}

static void	shell_start(void)
{
	char	*line;

	while (TRUE)
	{
		line = ft_readline(get_var("PS1", ALL_VARS));
		ft_system(&line);
		add_to_history_buff(line);
		ft_memdel((void**)&line);
	}
}

int			main(int argc, char **argv, char **environ)
{
	(void)argv;
	(void)argc;
	init_shell(environ);
	shell_start();
	return (EXIT_SUCCESS);
}
