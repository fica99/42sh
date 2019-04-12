/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:54:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/12 16:46:28 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_string(char *buf)
{
	char	*new_command;

	while ((new_command = ft_strchr(buf, ';')) != NULL)
	{
		if (buf == new_command)
		{
			buf++;
			continue;
		}
		else
			*new_command = '\0';
		make_command(buf);
		buf = ++new_command;
	}
	make_command(buf);
}

void	make_command(char *buf)
{
	char	**args;

	args = NULL;
	if (ft_strlen(buf) != 0)
	{
		if ((args = ft_strsplit(buf, ' ')))
		{
			args = spec_symbols(args);
			find_command(args);
			free_double_arr(args);
		}
		else
			ft_putchar('\n');
	}
}

char	**spec_symbols(char **args)
{
	short	i;
	char	*path;

	i = -1;
	while (args[++i])
	{
		if (!(ft_strcmp(args[i], "~")))
			if ((path = ft_getenv("HOME")))
				if (!(args[i] = ft_strdup(path)))
					print_error("echo", "malloc() error", NULL, ENOMEM);
		if (!(ft_strncmp(args[i], "$", 1)) && ft_strlen(args[i]) != 1)
			if ((path = ft_getenv(&(args[i][1]))))
				if (!(args[i] = ft_strdup(path)))
					print_error("echo", "malloc() error", NULL, ENOMEM);
	}
	return (args);
}