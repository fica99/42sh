/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/27 01:58:47 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	g_term.env_cp = copy_double_arr(environ);
	get_win_size();
	shell_start();
	free_double_arr(g_term.env_cp);
	return (EXIT_SUCCESS);
}

char	**copy_double_arr(char **arr)
{
	short	i;
	char	**arr1;

	if (!(arr1 = (char**)malloc(sizeof(char*) * (double_arr_len(arr) + 1))))
		print_error("minishell", "malloc() error", NULL, ENOMEM);
	i = -1;
	while (arr[++i])
		if (!(arr1[i] = ft_strdup(arr[i])))
			print_error("minishell", "malloc() error", NULL, ENOMEM);
	arr1[i] = NULL;
	return (arr1);
}

void	get_win_size(void)
{
	struct winsize	size;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) < 0)
		print_error("minishell", "ioctl() error", NULL, 0);
	g_term.ws_col = size.ws_col;
	g_term.ws_row = size.ws_row;
}

