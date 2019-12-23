/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:04:49 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/21 13:04:50 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

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
		ft_error("42sh", av[0], NULL, "too many arguments");
		return (-1);
	}
	if (!av[1])
		exit(g_last_exit_status);
	if (is_num(av[1]) < 0)
	{
		ft_error("42sh", av[0], NULL, "numeric argument required");
		exit(255);
	}
	exit(ft_atoi(av[1]));
	return (0);
}
