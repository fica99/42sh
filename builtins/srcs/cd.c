/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/26 16:15:20 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		init_curr_pwd(void)
{
	if (!(g_curr_dir = (char *)ft_memalloc(MAXDIR)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	if (!getcwd(g_curr_dir, MAXDIR))
		err_exit("42sh", "getcwd() error", NULL, NOERROR);
	set_env("PWD", g_curr_dir, ENV);
}

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

static char	*get_path(char **dir)
{
	char *path;

	if (!*dir || !ft_strcmp(*dir, "--"))
	{
		if (!(path = get_env("HOME", ENV)))
		{
			err("42sh", "cd", NULL, "HOME not set");
			return (NULL);
		}
	}
	else if (!ft_strcmp(*dir, "-"))
	{
		if (!(path = get_env("OLDPWD", ENV)))
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

int			cd(int ac, char **av)
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
	if (no_links || access(g_curr_dir, F_OK))
	{
		ft_bzero(g_curr_dir, ft_strlen(g_curr_dir));
		if (!(getcwd(g_curr_dir, MAXDIR)))
			err_exit("42sh", "getcwd() error", NULL, NOERROR);
	}
	if (!(path = get_path(dir)))
		return (-1);
	if (cdpath_handle(path, no_links) < 0)
		if (change_wdir(path, no_links) < 0)
			return (check_request(av, path));
	return (0);
}
