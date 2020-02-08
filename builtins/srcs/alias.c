/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 15:13:29 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/08 18:50:56 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char		print_alias(char *name)
{
	char	*value;

	value = get_hash_data(g_aliases_hash_table.table, name,
											g_aliases_hash_table.size);
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
			push_hash(g_aliases_hash_table.table, name, value,
											g_aliases_hash_table.size);
			ft_strdel(&name);
		}
	}
	return (result);
}
