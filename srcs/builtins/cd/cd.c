/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/18 17:10:35 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	check_request(char **argv, char *path)
{
	struct stat	buf;

	if (access(path, F_OK))
		print_error_withoutexit(argv[0], NULL, path, ENOENT);
	else
	{
		if (lstat(path, &buf) < 0)
			print_error("42sh", "lstat() error", NULL, 0);
		if (!S_ISDIR(buf.st_mode))
			print_error_withoutexit(argv[0], "not a directory", path, 0);
		else if (access(path, R_OK))
			print_error_withoutexit(argv[0], NULL, path, EACCES);
		else if (chdir(path) == -1)
			print_error("cd", "chdir() error", path, 0);
		else
			return (1);
	}
	return (-1);
}

char	check_ch_dir(int argc, char **argv)
{
	char	*path;

	if (argc >= 3)
	{
		if (argc > 3)
			print_error_withoutexit(argv[0], "too many arguments", NULL, 0);
		else if (argc == 3)
			print_error_withoutexit(argv[0], "string not in pwd", argv[1], 0);
		return (-1);
	}
	path = argv[1];
	if (argc == 1 || !ft_strcmp(argv[1], "--"))
		path = ft_getenv("HOME");
	else if (!ft_strcmp(argv[1], "-"))
	{
		ft_putstr_fd(path = ft_getenv("OLDPWD"), STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else if (!ft_strcmp(argv[1], "."))
		path = ft_getenv("PWD");
	if (check_request(argv, path) < 0)
		return (-1);
	return (1);
}

void	cd(int argc, char **argv, char **env_cp)
{
	char	buf[MAXDIR];

	(void)env_cp;
	if (check_ch_dir(argc, argv) < 0)
		return ;
	if (!(getcwd(buf, MAXDIR)))
		print_error("cd", "getcwd() error", argv[1], 0);
	if (ft_getenv("PWD"))
	{
		ft_setenv("OLDPWD", ft_getenv("PWD"));
		ft_setenv("PWD", buf);
	}
}
