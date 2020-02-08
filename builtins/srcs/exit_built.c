/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:04:49 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/08 18:40:34 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_num(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		str++;
	}
	return (0);
}

static void	free_globar_var(void)
{
	free(g_cur_wd);
	free_hash_table(g_bin_hash_table.table, g_bin_hash_table.size, 1);
	free_hash_table(g_builtins_hash_table.table, g_builtins_hash_table.size, 0);
	free_hash_table(g_aliases_hash_table.table, g_aliases_hash_table.size, 1);
	ft_free_dar(g_vars.vars);
	ft_free_dar(g_environ.vars);
}

int			exit_built(int ac, char **av, char **environ)
{
	(void)environ;
	if (ac > 2)
	{
		err("42sh", av[0], NULL, "too many arguments");
		return (-1);
	}
	free_readline();
	free_globar_var();
	if (!av[1])
		exit(g_last_exit_status);
	if (is_num(av[1]) < 0)
	{
		err("42sh", av[0], NULL, "numeric argument required");
		exit(255);
	}
	exit(ft_atoi(av[1]));
	return (0);
}
