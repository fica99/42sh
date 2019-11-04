/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/04 17:15:06 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	check_request(char **argv, char *path)
{
	struct stat	buf;

	if (path && !access(path, F_OK))
	{
		if (stat(path, &buf) < 0)
			err_exit(g_argv[0], "lstat() error", NULL, NOERROR);
		if (!S_ISDIR(buf.st_mode))
			err(argv[0], "not a directory", path, NOERROR);
		else if (access(path, R_OK))
			err(argv[0], NULL, path, EACCES);
		else if (chdir(path) == -1)
			err_exit(g_argv[0], "chdir() error", path, NOERROR);
		return (TRUE);
	}
	return (FALSE);
}

void	check_ch_dir(int argc, char **argv)
{
	char	*path;

	if ((argc == 1 || !ft_strcmp(argv[1], "--")))
		path = ft_getenv("HOME", g_env.env);
	else if (!ft_strcmp(argv[1], "-"))
	{
		ft_putstr_fd(path = ft_getenv("OLDPWD", g_env.env), STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else
		path = argv[1];
	if (!check_request(argv, path))
	{
		if ((path = check_cdpath(path)))
		{
			(!check_request(argv, path)) ? err(argv[0], NULL, path, ENOENT)
			: ft_putstr_fd(ft_strcat(path, "\n"), STDOUT_FILENO);
			ft_memdel((void**)&path);
			return ;
		}
		err(argv[0], NULL, path, ENOENT);
	}
}

char	*check_cdpath(char *path)
{
	char	**paths;
	char	*final_path;
	short	i;
	char	*cdpath;

	if (!(cdpath = ft_getenv("CDPATH", g_env.env)))
		return (NULL);
	if (!(paths = ft_strsplit(cdpath, ':')))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	if (!(final_path = ft_strnew(FT_PATH_MAX)))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	i = -1;
	while (paths[++i])
	{
		ft_strcat(final_path, *paths);
		ft_strcat(final_path, "/");
		ft_strcat(final_path, path);
		if (!access(final_path, F_OK))
			break ;
		ft_strclr(final_path);
	}
	ft_free_dar(paths);
	if (!(*final_path))
		ft_strcat(final_path, path);
	return (final_path);
}

void	cd(int argc, char **argv, char **env_cp)
{
	char	buf[MAXDIR];
	char	*pwd;

	(void)env_cp;
	if (argc >= 3)
	{
		if (argc > 3)
			err(argv[0], "too many arguments", NULL, NOERROR);
		else if (argc == 3)
			err(argv[0], "string not in pwd", argv[1], NOERROR);
		return ;
	}
	else
		check_ch_dir(argc, argv);
	if (!(getcwd(buf, MAXDIR)))
		err_exit(g_argv[0], "getcwd() error", argv[1], NOERROR);
	if ((pwd = ft_getenv("PWD", g_env.env)))
	{
		ft_setenv("OLDPWD", pwd);
		ft_setenv("PWD", buf);
	}
}
