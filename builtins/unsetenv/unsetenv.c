/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:55:51 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/26 11:15:49 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unsetenv(int argc, char **argv, char **environ)
{
	short  i;

	if (argc == 2)
	{
		if ((i = get_count_var(argv[1], environ)) >= 0)
		{
			while (environ[i + 1])
			{
				environ[i] = environ[i + 1];
				i++;
			}
			environ[i] = NULL;
			i = -1;
			while (environ[++i])
			{
				ft_putstr(environ[i]);
				ft_putchar('\n');
			}
		}
	}
	exit(0);
}
