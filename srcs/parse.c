/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:54:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/03 18:24:15 by aashara-         ###   ########.fr       */
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
		if (!(args = ft_strsplit(buf, ' ')))
		{
			print_error("minishell", "malloc() error", NULL, ENOMEM);
			exit(1);
		}
		args = spec_symbols(args);
		find_command(args);
		free_double_arr(args);
	}
}

char	**spec_symbols(char **args)
{
	short	i;

	i = -1;
	while (args[++i])
	{
		if (!(ft_strncmp(args[i], "~", 1)) && ft_strlen(args[i]) == 1)
			args[i] = get_var("HOME");
		if (!(ft_strncmp(args[i], "$", 1)) && ft_strlen(args[i]) != 1)
			args[i] = get_var(&(args[i][1]));
	}
	return (args);
}