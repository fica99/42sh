/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:54:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/30 18:49:04 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	parse_string(void)
{
	char	*new_command;
	char	*buf;

	buf = g_term.buffer;
	while ((new_command = ft_strchr(buf, ';')))
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
	if (*buf)
	{
		if ((args = ft_strsplit(buf, ' ')))
		{
			args = spec_symbols(args);
			find_command(args);
			free_double_arr(args);
		}
	}
}

char	**spec_symbols(char **args)
{
	short	i;
	char	*path;
	char	*arr;

	i = -1;
	while (args[++i])
	{
		if (*args[i] == '~')
		{
			if ((path = ft_getenv("HOME")))
			{
				arr = args[i];
				if (!(args[i] = ft_strjoin(path, arr + 1)))
					print_error("minishell", "malloc() error", NULL, ENOMEM);
				ft_memdel((void**)&arr);
			}
		}
		if (*args[i] == '$' && args[i] + 1)
		{
			if ((path = ft_getenv(args[i] + 1)))
			{
				arr = args[i];
				if (!(args[i] = ft_strdup(path)))
					print_error("minishell", "malloc() error", NULL, ENOMEM);
				ft_memdel((void**)&arr);
			}
		}
	}
	return (args);
}
