/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/02 16:05:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		main(int argc, char **argv, char **environ)
{
	init_global_var(argv, environ);
	if (argc == 1)
	{
		make_history_buff(&g_history);
		term_start();
		free_history(&g_history);
	}
	free_globar_var();
	return (EXIT_SUCCESS);
}

void	term_start(void)
{
	init_terminfo();
	init_line(&g_line);
	while (RUNNING)
	{
		g_flags = INIT_FLAGS;
		signal(SIGWINCH, win_handler);
		term_prompt();
		read_prompt();
		if (g_flags & TERM_EXIT)
			break ;
	}
	free_line(&g_line);
	reset_shell_mode();
}
