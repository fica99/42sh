/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/10 21:06:00 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*check_request(char **argv, char *path)
{
	struct stat	buf;

	if (path && !access(path, F_OK))
	{
		if (stat(path, &buf) < 0)
			print_error("42sh", "lstat() error", NULL, 0);
		if (!S_ISDIR(buf.st_mode))
		{
			print_error_withoutexit(argv[0], "not a directory", path, 0);
			return (SOMETHING);
		}
		else if (access(path, R_OK))
		{
			print_error_withoutexit(argv[0], NULL, path, EACCES);
			return (SOMETHING);
		}
		else if (chdir(path) == -1)
			print_error("cd", "chdir() error", path, 0);
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
			(!check_request(argv, path)) ? print_error_withoutexit(argv[0],
			NULL, path, ENOENT) : ft_putstr_fd(ft_strcat(path, "\n"), STDOUT_FILENO);
			ft_memdel((void**)&path);
			return ;
		}
		print_error_withoutexit(argv[0], NULL, path, ENOENT);
	}
}

char	*check_cdpath(char *path)
{
	char	**paths;
	char	*final_path;
	short	i;

	if (!(paths = ft_strsplit(ft_getenv("CDPATH"), ':')))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	if (!(final_path = ft_strnew(500)))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
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
			print_error_withoutexit(argv[0], "too many arguments", NULL, 0);
		else if (argc == 3)
			print_error_withoutexit(argv[0], "string not in pwd", argv[1], 0);
		return ;
	}
	else
		check_ch_dir(argc, argv);
	if (!(getcwd(buf, MAXDIR)))
		print_error("cd", "getcwd() error", argv[1], 0);
	if (ft_getenv("PWD"))
	{
		ft_setenv("OLDPWD", ft_getenv("PWD"));
		ft_setenv("PWD", buf);
	}
}
