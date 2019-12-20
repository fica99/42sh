/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/06 13:36:19 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	init_curr_pwd(void)
{
	if (!(g_curr_dir = (char *)ft_memalloc(MAXDIR)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	if (!getcwd(g_curr_dir, MAXDIR))
		err_exit("42sh", "getcwd() error", NULL, NOERROR);
	set_env("PWD", g_curr_dir, ENV);
}

int	check_request(char **argv, char *path)
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

char	**check_flags(char **av, t_flag *no_links)
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

int try_cdpath(char *path, char **cdpath, t_flag no_links)
{
	int i;
	char *tmp;
	int ret;

	ret = -1;
	i = -1;
	while (cdpath[++i])
	{
		if (!ft_strcmp(cdpath[i], ".."))
			continue ;
		if (!(tmp = ft_pathjoin(cdpath[i], path)))
			err_exit("42sh", "malloc() error", NULL, NOERROR);
		if (!(ret = change_wdir(tmp, no_links)))
		{
			if (no_links)
				ft_putln(tmp);
			else
				ft_putln(g_curr_dir);
			free(tmp);
			break ;
		}
		free(tmp);
	}
	return (ret);
}

int cdpath_handle(char *path, t_flag no_links)
{
	char *var_val;
	char **cdpath;
	int ret;

	if (!ft_strncmp(path, ".", 1) || !ft_strncmp(path, "..", 2))
		return (-1);
	if (!(var_val = get_env("CDPATH", ALL_ENV)))
		return (-1);
	if (!(cdpath = ft_strsplit(var_val, ':')))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	ret = try_cdpath(path, cdpath, no_links);
	ft_free_dar(cdpath);
	return (ret);
}

int	cd(int ac, char **av)
{
	char	**dir;
	t_flag	no_links;
	char	*path;

	(void)ac;
	no_links = 0;
	if (!(dir = check_flags(av, &no_links)))
	{
		ft_error("42sh", av[0], CD_USAGE, "invalid option\n");
		return (-1);
	}
	if (no_links || access(g_curr_dir, F_OK))
	{
		ft_bzero(g_curr_dir, ft_strlen(g_curr_dir));
		if (!(getcwd(g_curr_dir, MAXDIR)))
			err_exit("42sh", "getcwd() error", NULL, NOERROR);
	}
	if (!*dir || !ft_strcmp(*dir, "--"))
		path = get_env("HOME", ENV);
	else if (!ft_strcmp(*dir, "-"))
	{
		path = get_env("OLDPWD", ENV);
		ft_putln(path);
	}
	else
		path = *dir;
	if (cdpath_handle(path, no_links) < 0)
		if (change_wdir(path, no_links) < 0)
			return (check_request(av, path));
	return (0);
}
