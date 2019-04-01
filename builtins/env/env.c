/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:55:59 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/01 14:32:23 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_set(char **argv)
{
	short	j;

	j = 0;
	while (argv[++j])
	{
		if (!(ft_strchr(argv[j], '=')))
		{
			print_error(argv[0], argv[1], NULL, 2);
			return (-1);
		}
	}
	return (1);
}

void env(int argc, char **argv)
{
	short	j;

	j = 0;
	if (check_set(argv) < 0)
		return ;
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