/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/23 20:18:11 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			main(int argc, char **argv, char **environ)
{
	char	*termtype=getenv("TERM");
	int		ok;

	(void)argc;
	(void)argv;
	g_term.env_cp = copy_double_arr(environ);
	get_win_size();
	g_flags = INIT_FLAGS;

	ok = tgetent(NULL, termtype);
	if (ok == 1)
		shell_start();
	else if(ok == 0)
	{
		ft_putstr_fd("Termcap success! There is no match \
				the current version of the terminal.\n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	else
		ft_putstr_fd("Termcap failure!\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
