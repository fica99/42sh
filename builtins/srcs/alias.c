/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 15:13:29 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/09 20:19:32 by aashara-         ###   ########.fr       */
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

static void		print_all_aliases(void)
{
	short	i;
	char	*eq;
	char	*name;

	i = -1;
	if (!(name = ft_strnew(MAXNAMLEN)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	while (++i < g_aliases.cur_size)
	{
		eq = ft_strchr(g_aliases.vars[i], '=');
		ft_strncpy(name, g_aliases.vars[i], eq - g_aliases.vars[i]);
		print_alias(name);
	}
	ft_strdel(&name);
}

static char		is_invalid_name(char *name, char *value)
{
	char	result;

	result = EXIT_SUCCESS;
	if (!ft_strcmp(name, "-") || !ft_strcmp(name, "/") ||
	!ft_strcmp(name, "="))
	{
		err("42sh", "alias", "invalid alias name", name);
		result = EXIT_FAILURE;
	}
	else
	{
		if (*name)
			setvar(name, value, &g_aliases);
		else
		{
			err("42sh", "alias", ENOTFND, name);
			result = EXIT_FAILURE;
		}
	}
	return (result);
}

int				alias(int argc, char **argv, char **environ)
{
	char			*eq;
	char			result;
	char			*name;
	char			*value;

	(void)environ;
	if (argc == 1)
		print_all_aliases();
	result = EXIT_SUCCESS;
	while (*++argv)
	{
		if (!(eq = ft_strrchr(*argv, '=')))
			result = print_alias(*argv);
		else
		{
			if (!(name = ft_strsub(*argv, 0, eq - *argv)))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
			if (!(value = ft_strdup(*argv + (eq - *argv) + 1)))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
			result = is_invalid_name(name, value);
			ft_strdel(&value);
			ft_strdel(&name);
		}
	}
	return (result);
}
