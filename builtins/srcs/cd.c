/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/05 20:07:35 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	init_curr_pwd(void)
{
	if (!(g_curr_dir = getwd(NULL)))
		err_exit(g_argv[0], "getwd() error", NULL, NOERROR);
	ft_setenv("PWD", g_curr_dir);
}

char	check_request(char **argv, char *path)
{
	struct stat	buf;

	if (path && !access(path, F_OK))
	{
		if ((stat(path, &buf)) < 0)
			err_exit(g_argv[0], "stat() error", NULL, NOERROR);
		if (!S_ISDIR(buf.st_mode))
			err(argv[0], "not a directory", path, NOERROR);
		else if (access(path, R_OK))
			err(argv[0], NULL, path, EACCES);
		return (TRUE);
	}
	err("42sh", argv[0], "no such file or directory", path);
	return (FALSE);
}

char	**check_flags(char **av, t_cdf *flags)
{
	int i;
	int j;

	j = 1;
	i = 1;
	flags->P = 0;
	flags->L = 0;
	while (av[j] && av[j][0] == '-')
	{
		while (av[j][i])
		{
			if (**av == 'L')
				flags->L = 1;
			else if (**av == 'P')
				flags->P = 1;
			else
				return (0);
			i++;
		}
		j++;
		i = 0;
	}
	return (&av[j]);
}

void	cd(char **av)
{
	char	**dir;
	t_cdf	flags;
	char	*path;

	if (!(dir = check_flags(av, &flags)))
	{
		ft_error("42sh", av[0], CD_USAGE, "invalid option\n");
		return ;
	}
	if (!*dir || !ft_strcmp(*dir, "--"))
		path = ft_getenv("HOME", g_env.env);
	else if (!ft_strcmp(*dir, "-"))
		path = ft_getenv("OLDPWD", g_env.env);
	else
		path = (*dir);
	if ((chdir(path)) < 0)
		check_request(av, path);
	else
		rewrite(path, flags);
}

void	pwd(char **av)
{
	char	*dir;
	t_cdf	flags;

	dir = 0;
	if (!check_flags(av, &flags))
		ft_error("42sh", av[0], PWD_USAGE, NULL);
	if (!flags.P)
		getwd(dir);
	else
		dir = ft_strdup(g_curr_dir);
	ft_putstr_fd(dir, STDOUT_FILENO);
	free(dir);
}
