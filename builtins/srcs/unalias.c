/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 12:56:01 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/09 13:43:47 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void		remove_all_aliases(void)
{
	short	i;

	i = -1;
	while (++i < g_aliases.cur_size)
		ft_strdel(&(g_aliases.vars[i]));
	g_aliases.cur_size = 0;
}

int				unalias(int argc, char **argv, char **environ)
{
	char	result;

	(void)environ;
	result = EXIT_SUCCESS;
	if (argc == 1)
	{
		err("unalias", "usage", UNALIAS_USAGE, NULL);
		return (EXIT_FAILURE);
	}
	if (!ft_strcmp(*++argv, "-a"))
		remove_all_aliases();
	else
		--argv;
	while (*++argv)
	{
		if (ft_getvar(*argv, g_aliases.vars))
			ft_unsetvar(*argv, &g_aliases);
		else
		{
			err("42sh", "unalias", ENOTFND, *argv);
			result = EXIT_FAILURE;
		}
	}
	return (result);
}
