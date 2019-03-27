/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:55:59 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/27 16:45:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_set(char **argv)
{
	short	j;

	j = 0;
	while (argv[++j])
	{
		if (!(ft_strchr(argv[j], '=')))
		{
			ft_putstr("env: ");
			ft_putstr(argv[j]);
			print_error("No such file or directory", 9);
		}
	}
}

void env(int argc, char **argv)
{
	short	j;

	j = 0;
	check_set(argv);
	print_environ();
	if (argc != 1)
	{
		j = 0;
		while (argv[++j])
		{
				ft_putstr(argv[j]);
				ft_putchar('\n');
		}
	}
}