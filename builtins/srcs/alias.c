/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 15:13:29 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/08 20:39:11 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char		print_alias(char *name)
{
	char	*value;

	value = ft_getvar(name, g_aliases.vars);
	if (!value)
	{
		err("42sh", "alias", ENOTFND, name);
		return (EXIT_FAILURE);
	}
	ft_putstr("alias ");
	ft_putstr(name);
	ft_putstr("=\'");
	ft_putstr(value);
	ft_putendl("\'");
	return (EXIT_SUCCESS);
}

int				alias(int argc, char **argv, char **environ)
{
	char			*eq;
	char			result;
	char			*name;
	char			*value;

	(void)environ;
	(void)argc;
	if (g_aliases.malloc_size == 0)
		set_variables(&g_aliases, NULL, VAR_DEF_MALLOC_SIZE);
	result = EXIT_SUCCESS;
	while (*++argv)
	{
		if (!(eq = ft_strchr(*argv, '=')))
			result = print_alias(*argv);
		else
		{
			if (!(name = ft_strsub(*argv, 0, eq - *argv)))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
			if (!(value = ft_strdup(*argv + (eq - *argv) + 1)))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
			setvar(name, value, &g_aliases);
			ft_strdel(&value);
			ft_strdel(&name);
		}
	}
	return (result);
}
