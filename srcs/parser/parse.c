/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:54:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/15 22:27:27 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	parse_string(t_term *term)
{
	char	*new_command;
	char	*buffer;

	buffer = term->buffer;
	while ((new_command = ft_strchr(buffer, ';')))
	{
		if (buffer != new_command)
		{
			*new_command = '\0';
			make_command(buffer, term);
		}
		buffer = ++new_command;
	}
	make_command(buffer, term);
}

void	make_command(char *buff, t_term *term)
{
	char	**args;
	short	i;

	if (!buff || !(*buff) || !(args = ft_strsplit(buff, ' ')))
		return ;
	i = -1;
	while (args[++i])
		args[i] = spec_symbols(args[i]);
	find_command(args, term);
	ft_free_dar(args);
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
