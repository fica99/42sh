/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:54:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/27 23:45:09 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	parse_string(char *buf, t_hash **hash_table, short hash_table_size,
t_history *history)
{
	char	*new_command;

	while ((new_command = ft_strchr(buf, ';')))
	{
		if (buf != new_command)
		{
			*new_command = '\0';
			make_command(buf, hash_table, hash_table_size, history);
		}
		buf = ++new_command;
	}
	make_command(buf, hash_table, hash_table_size, history);
}

void	make_command(char *buf, t_hash **hash_table, short hash_table_size,
t_history *history)
{
	char	**args;
	short	i;

	if (!buf || !(*buf) || !(args = ft_strsplit(buf, ' ')))
		return ;
	i = -1;
	while (args[++i])
		args[i] = spec_symbols(args[i]);
	find_command(args, hash_table, hash_table_size, history);
	free_double_arr(args);
}

char	*spec_symbols(char *args)
{
	char	*path;
	char	*arr;

	if (*args == '~')
	{
		if ((path = ft_getenv("HOME")))
		{
			arr = args;
			if (!(args = ft_strjoin(path, arr + 1)))
				print_error("42sh", "malloc() error", NULL, ENOMEM);
			ft_memdel((void**)&arr);
		}
	}
	if (*args == '$' && args + 1)
	{
		if ((path = ft_getenv(args + 1)))
		{
			arr = args;
			if (!(args = ft_strdup(path)))
				print_error("42sh", "malloc() error", NULL, ENOMEM);
			ft_memdel((void**)&arr);
		}
	}
	return (args);
}
