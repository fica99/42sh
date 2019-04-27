/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/28 00:21:05 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term.h"

int		main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	g_term.env_cp = copy_double_arr(environ);
	get_win_size();
	term_start();
	free_double_arr(g_term.env_cp);
	return (EXIT_SUCCESS);
}

void	term_start(void)
{
	while (RUNNING)
	{
		g_flags = INIT_FLAGS;
		signalling();
		term_prompt();
		get_cur_cord();
		g_term.x_start = g_term.x_cur;
		g_term.y_start = g_term.y_cur;
		read_prompt();
		if (!(g_flags & TERM_SIGINT))
			parse_string();
		ft_memdel((void**)&(g_term.buffer));
	}
}

void	term_prompt(void)
{
	char	*path;
	char	hostname[FT_HOST_NAME_MAX];

	gethostname(hostname, FT_HOST_NAME_MAX);
	RED(STDERR_FILENO);
	ft_putchar_fd('[', STDERR_FILENO);
	CYAN(STDIN_FILENO);
	ft_putstr_fd(ft_getenv("USER"), STDIN_FILENO);
	RED(STDIN_FILENO);
	ft_putchar_fd('@', STDIN_FILENO);
	GREEN(STDIN_FILENO);
	ft_putstr_fd(hostname, STDIN_FILENO);
	RED(STDIN_FILENO);
	ft_putchar_fd(' ', STDIN_FILENO);
	YELLOW(STDIN_FILENO);
	path = check_path();
	ft_putstr_fd(path, STDIN_FILENO);
	RED(STDIN_FILENO);
	ft_putchar_fd(']', STDIN_FILENO);
	PURPLE(STDIN_FILENO);
	ft_putstr_fd(" $> ", STDIN_FILENO);
	STANDART(STDIN_FILENO);
}