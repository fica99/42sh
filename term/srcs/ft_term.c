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

	signalling();
	init_readline();
	while (RUNNING)
	{
		g_flags = INIT_FLAGS;
		if (!(line = ft_readline(get_env("PS1", ALL_ENV), EMACS)))
			continue ;
		check_valid_string(line);
		add_to_history_buff(line);
		ft_memdel((void**)&line);
		if (g_flags & TERM_EXIT)
			break ;
	}
	free_readline();
}

int		status_update(int rules[RULES_NUM][3], int *status, t_lex_tkn **list)
{
	int i;

	i = 0;
	while (i < RULES_NUM)
	{
		if (rules[i][0] == (*list)->class
		&& rules[i][1] == (*(list + 1))->class)
		{
			*status = rules[i][2];
			return (0);
		}
		i++;
	}
	return (-1);
}

int		check_valid_list(t_lex_tkn **list)
{
	int			status;
	static int	rules[RULES_NUM][3] = {{0, 0, 0}, {0, 1, 1}, {1, 0, 1},
	{0, 3, 0}, {3, 0, 0}, {3, 3, 0}, {2, 1, 1}, {2, 0, 0},
	{0, 2, 0}, {0, 10, 0}, {2, 10, 255}, {5, 10, 255}, {3, 10, 0}};

	status = 0;
	while (*(list + 1))
	{
		if (status_update(rules, &status, list) < 0)
			return (syntax_err(*(list + 1)));
		if (status == 255)
			/*
			** дополнить строку
			*/
			return (-1);
		list++;
	}
	return (0);
}

void	check_valid_string(char *buffer)
{
	t_lex_tkn	**tokens;

	tokens = lex_get_tkns(&buffer);
	if (!check_valid_list(tokens))
		parse(tokens);
	lex_del_tkns(tokens);
}
