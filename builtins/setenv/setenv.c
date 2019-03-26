/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:13:34 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/26 12:53:05 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_setenv(int argc, char **argv)
{
	int	j;
	int	i;

	if (argc == 1)
		print_environ(env_cp);
	else
	{
		j = 0;
		i = 0;
		while (env_cp[i])
			i++;
		while (argv[++j])
		{
			if (!(ft_strchr(argv[j], '=')))
				continue ;
			else
				env_cp[i++] = argv[j];
		}
	}
	exit(0);
}

void	set_env(char *name, char *new_value)
{
	unsigned short	j;

	j = get_count_var(name, env_cp);
	free(env_cp[j]);
	name = ft_strjoin(name, "=");
	env_cp[j] = ft_strjoin(name, new_value);
}