/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:55:59 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/26 15:00:51 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	env(int argc, char **argv)
{
	int		j;
	char	**env_cp;

	(void)argc;
	(void)argv;
	env_cp = g_env.env;
	j = -1;
	while (env_cp[++j])
	{
		ft_putstr(env_cp[j]);
		ft_putchar('\n');
	}
	return (0);
}
