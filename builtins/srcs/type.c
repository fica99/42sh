/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara <aashara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:00:12 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/10 12:47:55 by aashara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char		*type_error(char *arg)
{
	err("42sh", "type", "not found", arg);
	return (NULL);
}

static char		*get_fname_type(char *arg, char **environ)
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
			if ((check_path_var(arg, environ)) == 0)
				return (arg);
			return (type_error(arg));
		}
		else
			return (type_error(arg));
	}
	if (!(fname = find_in_path(arg, environ)))
		return (type_error(arg));
	return (fname);
}

static int		isfile(char *argv, char **environ)
{
	char	*res;

	res = get_fname_type(argv, environ);
	if (!res)
		return (-1);
	ft_putstr_fd(argv, STDOUT_FILENO);
	ft_putstr_fd(" is ", STDOUT_FILENO);
	ft_putstr_fd(res, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_strdel(&res);
	return (0);
}

static int		isbuiltin(char *argv)
{
	if (!((t_builtin)get_hash_data(g_builtins_hash_table.table,
					argv, g_builtins_hash_table.size)))
		return (0);
	return (1);
}

int				ft_type(int argc, char **argv, char **environ)
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
		else if (isalias(argv[i]))
			;
		else
			isfile(argv[i], environ);
		i++;
	}
	return (0);
}
