/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:54:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/27 21:42:28 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_string(char *buf)
{
	char	**args;
	int		i;

	args = ft_strsplit(buf, ' ');
	i = -1;
	while (args[++i])
	{
		if (!(ft_strcmp(args[i], "~")))
			args[i] = get_var("HOME");
		if (*args[i] == '$' && ft_strlen(args[i]) != 1)
		{
			if (args[i][1] == '(' && args[i][ft_strlen(args[i]) - 1] == ')')
			{
				args[i] = &(args[i][2]);
				args[i][ft_strlen(args[i]) - 1] = '\0';
			}
			else
				args[i] = &(args[i][1]);
			args[i] = get_var(args[i]);
		}
	}
	return (args);
}