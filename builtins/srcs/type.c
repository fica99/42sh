/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:00:12 by jijerde           #+#    #+#             */
/*   Updated: 2020/01/21 17:41:31 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static char		*get_fname_type(char *arg)
{
	char			*fname;
	struct stat		stbuf;

	if (ft_strcmp(".", arg) == 0 || ft_strcmp("..", arg) == 0)
		return (type_error(arg));
	if (ft_strchr(arg, '/'))
	{
		if (lstat(arg, &stbuf) != -1)
		{
			if (!(S_ISREG(stbuf.st_mode)))
				return (type_error(arg));
			if ((check_path_var(arg)) == 0)
				return (arg);
			return (type_error(arg));
		}
		else
			return (type_error(arg));
	}
	if (!(fname = find_in_path(arg)))
		return (type_error(arg));
	return (fname);
}

static int		isfile(char *argv)
{
	char *res;

	res = get_fname_type(argv);
	if (!res)
		return (-1);
	ft_putstr_fd(argv, STDOUT_FILENO);
	ft_putstr_fd(" is ", STDOUT_FILENO);
	ft_putstr_fd(res, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

static int		isbuiltin(char *argv)
{
	if (!((t_builtin)get_hash_data(g_built_table.table,
					argv, g_built_table.size)))
		return (0);
	return (1);
}

static int		iskeyword(char *argv)
{
	t_keyw *keyw;

	keyw = &g_keyw;
	while (keyw)
	{
		if ((ft_strcmp(argv, keyw->data)) == 0)
			return (1);
		keyw = keyw->next;
	}
	return (0);
}

int				ft_type(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc < 2)
		return (0);
	while (argv[i])
	{
		if (isbuiltin(argv[i]))
		{
			ft_putstr_fd(argv[i], STDOUT_FILENO);
			ft_putstr_fd(" is a shell builtin\n", STDOUT_FILENO);
		}
		else if (iskeyword(argv[i]))
		{
			ft_putstr_fd(argv[i], STDOUT_FILENO);
			ft_putstr_fd(" is a shell keyword\n", STDOUT_FILENO);
		}
		else
			isfile(argv[i]);
		i++;
	}
	return (0);
}
