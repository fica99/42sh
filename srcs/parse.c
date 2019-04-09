/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:54:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/28 15:53:43 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_string(char *buf)
{
	char	**args;
	char	*new_command;
	pid_t	p;
	int		status;

	while ((new_command = ft_strchr(buf, ';')) != NULL)
	{
		*new_command = '\0';
		args = ft_strsplit(buf, ' ');
		args = spec_symbols(args);
		p = make_process();
		if (!p)
			find_command(args);
		else
			waitpid(p, &status, 0);
		buf = ++new_command;
	}
	args = ft_strsplit(buf, ' ');
	args = spec_symbols(args);
	if (!p)
		find_command(args);
	else
		waitpid(p, &status, 0);
	find_command(args);
}

char	**spec_symbols(char **args)
{
	short	i;

	i = -1;
	while (args[++i])
	{
		if (!(ft_strcmp(args[i], "~")))
			args[i] = get_var("HOME");
		if (*args[i] == '$' && ft_strlen(args[i]) != 1)
		{
			args[i] = &(args[i][1]);
			args[i] = get_var(args[i]);
		}
	}
	return (args);
}