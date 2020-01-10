/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/08 19:46:48 by aashara-         ###   ########.fr       */
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
	t_job 	*last_job;

	signalling();
	init_readline();
	init_jobs();
	last_job = NULL;
	while (RUNNING)
	{
		if (!(line = ft_readline(get_env("PS1", ALL_ENV), EMACS)))
			continue ;
		last_job = check_valid_string(line, last_job);
		add_to_history_buff(line);
		ft_memdel((void**)&line);
	}
	free_readline();
}

t_job	*check_valid_string(char *buffer, t_job *last_job)
{
	t_lex_tkn	**tokens;
	t_ast		*root;

	tokens = lex_get_tkns(&buffer);
	if (!tokens || !*tokens || (*tokens)->type == T_END)
		return (0);
	if (!make_ast(tokens, &root))
	{
		parse(root);
		last_job = exec_jobs(last_job->next);
	}
	//ft_free_jobs(g_first_job);
	//g_first_job = NULL;
	clean_tree(root);
	lex_del_tkns(tokens);
	return (last_job);
}
