/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:13:34 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/26 19:17:09 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_setenv(int argc, char **argv)
{
	int	j;
	int	i;

	if (argc == 1)
		print_environ();
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
