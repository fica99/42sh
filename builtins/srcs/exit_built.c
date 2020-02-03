/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:04:49 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/26 17:31:26 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "interpretator.h"

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

int			exit_built(int ac, char **av)
{
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
