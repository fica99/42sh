/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:13:34 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/26 11:25:25 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_setenv(int argc, char **argv, char **environ)
{
	int	j;
	int	i;

	if (argc == 1)
		print_environ(environ);
	else
	{
		j = 0;
		i = 0;
		while (environ[i])
			i++;
		while (argv[++j])
		{
			if (!(ft_strchr(argv[j], '=')))
				continue ;
			else
				environ[i++] = argv[j];
		}
	}
	exit(0);
}

char	**set_env(char **environ, char *name, char *new_value)
{
	unsigned short	j;

	j = get_count_var(name, environ);
	free(environ[j]);
	environ[j] = ft_strjoin(name, new_value);
	return (environ);
}