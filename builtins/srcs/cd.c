/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/01 11:20:18 by lcrawn           ###   ########.fr       */
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

char	check_request(char **argv, char *path)
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
		return (TRUE);
	}
	err("42sh", argv[0], "no such file or directory", path);
	return (FALSE);
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

void	cd(char **av)
{
	char	**dir;
	t_flag	no_links;
	char	*path;

	no_links = 0;
	if (!(dir = check_flags(av, &no_links)))
	{
		ft_error("42sh", av[0], CD_USAGE, "invalid option\n");
		return ;
	}
	if (!*dir || !ft_strcmp(*dir, "--"))
		path = get_env("HOME", ENV);
	else if (!ft_strcmp(*dir, "-"))
		path = get_env("OLDPWD", ENV);
	else {
		path = *dir;
	}
	if ((change_wdir(path, no_links)) < 0)
		check_request(av, path);
}

void	pwd(char **av)
{
	char	*dir;
	t_flag	no_links;

	if (!check_flags(av, &no_links))
	{
		ft_error("42sh", av[0], PWD_USAGE, NULL);
		return ;
	}
	if (no_links)
	{
		if (!(dir = (char *)malloc(MAXDIR)))
			err_exit("42sh", "malloc() error", NULL, NOERROR);
		dir[MAXDIR - 1] = 0;
		if (!getcwd(dir, MAXDIR))
			err_exit("42sh", "getcwd() error", NULL, NOERROR);
	}
	else
		dir = ft_strdup(g_curr_dir);
	ft_putstr_fd(dir, STDOUT_FILENO);
	ft_putchar('\n');
	free(dir);
}
