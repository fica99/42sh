/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:43:47 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/19 21:46:19 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t	check_ch_dir(int argc , char **argv, char **env)
{
	if (argc >= 3)
	{
		if (argc > 3)
			ft_putstr("cd: too many arguments\n");
		else
		{
			ft_putstr("cd: string not in pwd: ");
			ft_putstr(argv[1]);
			ft_putchar('\n');
		}
		exit (-1);
	}
	else
	{
		check_request(argc, argv, env);
	}
	return (1);
}

uint8_t	check_request(int argc, char  **argv, char **env)
{
	if (argc == 1)
		argv[1] = (get_var("HOME", env));
	if (ft_strcmp(argv[1], "-") == 0)
		argv[1] = get_var("OLDPWD", env);
	if (chdir(argv[1]) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putstr(argv[1]);
		ft_putchar('\n');
		exit(-1);
	}
	return (1);	
}

uint8_t	add_flag(uint8_t flags, char flag)
{
	if (flag == 'e')
		return (flags | 1);
	if (flag == 'E')
		return (flags | 2);
	if (flag == 'n')
		return (flags | 4);
	return (0);
}

uint8_t	is_flags(uint8_t flags, char flag)
{
	if (flag == 'e' && (flags & 1) == 1)
		return (1);
	if (flag == 'E' && (flags & 2) == 2)
		return (1);
	if (flag == 'n' && (flags & 4) == 4)
		return (1);
	return (0);
}

uint8_t	check_symbol(char s)
{
	if (s == '\n')
		write(1, "\n", 1);
	else if (s == '\\')
		write(1, "\\", 2);
	else if (s == '\a')
		write(1, "\a", 2);
	else if (s == '\b')
		write(1, "\b", 2);
	else if (s == '\r')
		write(1, "\r", 2);
	else if (s == '\f')
		write(1, "\f", 2);
	else if (s == '\t')
		write(1, "\t", 2);
	else if (s == '\v')
		write(1, "\v", 2);
	else
		return (0);
	return (1);
}