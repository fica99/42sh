/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/12 16:50:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
# include <dirent.h>
# include <unistd.h>

# define MAXDIR 4097

char	check_request(int argc, char  **argv)
{
	char	*path;

	path = argv[1];
	if (argc == 1 || ft_strcmp(argv[1], "--") == 0)
		path = ft_getenv("HOME");
	else if (ft_strcmp(argv[1], "-") == 0)
		path = ft_getenv("OLDPWD");
	if (access(path, F_OK))
		print_error_withoutexit(argv[0], NULL, path, 2);
	else if (access(path, R_OK | X_OK))
		print_error_withoutexit(argv[0], NULL, path, 13);
	else if (chdir(path) == -1)
		print_error("cd", "chdir() error", path, 0);
	else
		return (1);
	return (-1);
}

char	check_ch_dir(int argc , char **argv)
{
	if (argc >= 3)
	{
		if (argc > 3)
			print_error_withoutexit(argv[0], "too many arguments", NULL, 0);
		else
			print_error_withoutexit(argv[0], "string not in pwd", argv[1], 0);
		return (-1);
	}
	else
	{
		if (check_request(argc, argv) < 0)
			return (-1);
	}
	return (1);
}

void	cd(int argc, char **argv)
{
	char	buf[MAXDIR];

	if (check_ch_dir(argc, argv) < 0)
		return;
	if (!(getcwd(buf, MAXDIR)))
		print_error("cd", "getcwd() error", argv[1], 0);
	set_env("OLDPWD", ft_getenv("PWD"));
	set_env("PWD", buf);
}

