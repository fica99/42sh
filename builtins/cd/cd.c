/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/01 14:31:14 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
# include <dirent.h>
# include <unistd.h>

# define MAXDIR 4097

char	check_request(int argc, char  **argv)
{
	char	*path;

	path = NULL;
	if (argc == 1 || ft_strcmp(argv[1], "--") == 0)
		path = get_var("HOME");
	else if (ft_strcmp(argv[1], "-") == 0)
		path = get_var("OLDPWD");
	if (path)
		argv[1] = path;
	if (access(argv[1], F_OK))
		print_error(argv[0], NULL, argv[1], 2);
	else if (access(argv[1], R_OK | X_OK))
		print_error(argv[0], NULL, argv[1], 13);
	else if (chdir(argv[1]) == -1)
		print_error(argv[0], "chdir() error", argv[1], 0);
	else
		return (1);
	return (-1);
}

char	check_ch_dir(int argc , char **argv)
{
	if (argc >= 3)
	{
		if (argc > 3)
			print_error(argv[0], "too many arguments", NULL, 0);
		else
			print_error(argv[0], "string not in pwd", argv[1], 0);
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
	getcwd(buf, MAXDIR);
	set_env("OLDPWD", get_var("PWD"));
	set_env("PWD", buf);
}

