/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:54:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/30 21:09:40 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_string(char *buf)
{
	char	*new_command;
	pid_t	p;
	int		status;

	while ((new_command = ft_strchr(buf, ';')) != NULL)
	{
		*new_command = '\0';
		p = make_process();
		if (!p)
			break ;
		else
			waitpid(p, &status, 0);
		buf = ++new_command;
	}
	make_command(buf);
}

void	make_command(char *buf)
{
	char	**args;

	if (!(args = ft_strsplit(buf, ' ')))
		print_error("minishell", "malloc() error", NULL, ENOMEM);
	args = spec_symbols(args);
	find_command(args);
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