/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/05 15:06:40 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_request(char **argv, char *path)
{
	struct stat	buf;

	if (path && !access(path, F_OK))
	{
		if ((stat(path, &buf)) < 0)
			err_exit("42sh", "stat() error", NULL, NOERROR);
		if (!S_ISDIR(buf.st_mode))
			err(argv[0], "not a directory", path, NOERROR);
		else if (access(path, R_OK))
			err(argv[0], NULL, path, EACCES);
	}
	else
		err("42sh", argv[0], "no such file or directory", path);
	return (-1);
}

char		**check_flags(char **av, t_flag *no_links)
{
	int i;
	int j;

	j = 1;
	i = 0;
	while (av[j] && av[j][0] == '-')
	{
		if (av[j][i + 1] == 0 || av[j][i + 1] == '-')
			return (&av[j]);
		while (av[j][++i])
		{
			if (av[j][i] == 'L')
				*no_links = 0;
			else if (av[j][i] == 'P')
				*no_links = 1;
			else
				return (0);
		}
		j++;
		i = 0;
	}
	return (&av[j]);
}

static char	*get_path(char **dir, char **environ)
{
	char *path;

	if (!*dir || !ft_strcmp(*dir, "--"))
	{
		if (!(path = ft_getvar("HOME", environ)))
		{
			err("42sh", "cd", NULL, "HOME not set");
			return (NULL);
		}
	}
	else if (!ft_strcmp(*dir, "-"))
	{
		if (!(path = ft_getvar("OLDPWD", environ)))
		{
			err("42sh", "cd", NULL, "OLDPWD not set");
			return (NULL);
		}
		ft_putendl(path);
	}
	else
		path = *dir;
	return (path);
}

int			cd(int ac, char **av, char **environ)
{
	char	**dir;
	t_flag	no_links;
	char	*path;

	(void)ac;
	no_links = 0;
	if (!(dir = check_flags(av, &no_links)))
	{
		err("42sh", av[0], CD_USAGE, "invalid option\n");
		return (-1);
	}
	if (no_links || access(g_cur_wd, F_OK))
	{
		ft_bzero(g_cur_wd, ft_strlen(g_cur_wd));
		if (!(getcwd(g_cur_wd, PATH_MAX)))
			err_exit("42sh", "getcwd() error", NULL, NOERROR);
	}
	if (!(path = get_path(dir, environ)))
		return (-1);
	if (cdpath_handle(path, no_links, environ) < 0)
		if (change_wdir(path, no_links, environ) < 0)
			return (check_request(av, path));
	return (0);
}
