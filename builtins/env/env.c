/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:55:59 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/23 15:58:13 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t	check_set(char **argv)
{
	short	j;

	j = 0;
	while (argv[++j])
	{
		if (!(ft_strchr(argv[j], '=')))
		{
			ft_putstr("env: ");
			ft_putstr(argv[j]);
			ft_putstr(": No such file or directory\n");
			return (1);
		}
	}
	return (0);
}

uint8_t env(int argc, char **argv, char **environ)
{
	short	i;
	short	j;

	i = -1;
	if (check_set(argv))
		return (1);
	while (environ[++i])
	{
		ft_putstr(environ[i]);
		ft_putchar('\n');
	}
	if (argc != 1)
	{
		j = 0;
		while (argv[++j])
		{
				ft_putstr(argv[j]);
				ft_putchar('\n');
		}
	}
	return (0);
}

int main(int argc, char **argv, char **environ)
{
    env(argc, argv, environ);
    return (0);
}