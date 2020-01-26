/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:09:22 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/26 15:14:52 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	setenv_built(int ac, char **av)
{
	if (ac > 3)
	{
		err("42sh", av[0], NULL, "too many arguments");
		return (1);
	}
	if (ac == 1)
		ft_putdar(g_env.env);
	else
		ft_setenv(av[1], av[2], &g_env);
	return (0);
}
