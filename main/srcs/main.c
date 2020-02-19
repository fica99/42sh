/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:41:23 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/19 22:24:33 by aashara-         ###   ########.fr       */
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

static void		lex_status_proc(void)
{
	if (g_lex_stat == LS_ERR)
	{
		err("42sh", "unexpected syntax error", NULL, NOERROR);
		g_last_exit_status = 1;
		set_var("?", "1", ALL_VARS);
		return ;
	}
	g_last_exit_status = 130;
	set_var("?", "130", ALL_VARS);
}

int			ast_handle(t_lex_tkn ***tokens, t_ast **root, char **line)
{
	int ret;

	ret = make_ast(*tokens, root);
	if (ret == 2)
	{
		clean_tree(*root);
		*root = NULL;
		if (al_p_lo(tokens, line))
			return (1);
		return (ast_handle(tokens, root, line));
	}
	return (ret);
}

void		ft_system(char **line)
{
	t_lex_tkn	**tokens;
	t_ast		*root;

	tokens = lex_get_tkns(line);
	if (g_lex_stat != LS_OK)
	{
		lex_status_proc();
		return ;
	}
	tokens = alias_handle(tokens);
	if (tokens && *tokens && (*tokens)->type != T_END)
	{
		root = NULL;
		if (!ast_handle(&tokens, &root, line))
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
//	t_lex_tkn **tkns;

	while (tcgetpgrp(STDIN_FILENO) != getpgrp())
		;
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
