/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/21 22:49:23 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*check_request(char **argv, char *path)
{
	struct stat	buf;

	if (path && !access(path, F_OK))
	{
		if (stat(path, &buf) < 0)
			err_exit("42sh", "lstat() error", NULL, NOERROR);
		if (!S_ISDIR(buf.st_mode))
		{
			err(argv[0], "not a directory", path, NOERROR);
			return (SOMETHING);
		}
		else if (access(path, R_OK))
		{
			err(argv[0], NULL, path, EACCES);
			return (SOMETHING);
		}
		else if (chdir(path) == -1)
			err_exit("cd", "chdir() error", path, NOERROR);
		else
			return (SOMETHING);
	}
	return (NULL);
}

void	check_ch_dir(int argc, char **argv)
{
	char	*path;

	if ((argc == 1 || !ft_strcmp(argv[1], "--")) && ft_getenv("HOME"))
		path = ft_getenv("HOME");
	else if (!ft_strcmp(argv[1], "-") && ft_getenv("OLDPWD"))
	{
		ft_putstr_fd(path = ft_getenv("OLDPWD"), STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else
		path = argv[1];
	if (!check_request(argv, path))
	{
		if (ft_getenv("CDPATH") && (path = check_cdpath(path)))
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

	if (!(paths = ft_strsplit(ft_getenv("CDPATH"), ':')))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	if (!(final_path = ft_strnew(500)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
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
	if (*final_path == '\0')
		ft_strcat(final_path, path);
	return (final_path);
}

void	cd(int argc, char **argv, char **env_cp)
{
	char	buf[MAXDIR];

	(void)env_cp;
	if (argc >= 3)
	{
		if (argc > 3)
			err("too many arguments", NULL, NOERROR);
		else if (argc == 3)
			err("string not in pwd", argv[1], NOERROR);
		return ;
	}
	else
		check_ch_dir(argc, argv);
	if (!(getcwd(buf, MAXDIR)))
		err_exit("getcwd() error", argv[1], NOERROR);
	if (ft_getenv("PWD"))
	{
		ft_setenv("OLDPWD", ft_getenv("PWD"));
		ft_setenv("PWD", buf);
	}
}
