/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:55:51 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/26 12:53:59 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unsetenv(int argc, char **argv)
{
	short  i;

	if (argc == 2)
	{
		if ((i = get_count_var(argv[1], env_cp)) >= 0)
		{
			while (env_cp[i + 1])
			{
				env_cp[i] = env_cp[i + 1];
				i++;
			}
			env_cp[i] = NULL;
			i = -1;
			while (env_cp[++i])
			{
				ft_putstr(env_cp[i]);
				ft_putchar('\n');
			}
		}
	}
	exit(0);
}
