/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/27 21:43:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
# include <dirent.h>
# include <unistd.h>

# define MAXDIR 4097

void	check_request(int argc, char  **argv)
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
	if (access(argv[1], R_OK | X_OK))
		print_error(argv[0], NULL, argv[1], 13);
	if (chdir(argv[1]) == -1)
		print_error(argv[0], "chdir() error", argv[1], 0);
}

void	check_ch_dir(int argc , char **argv)
{
	if (argc >= 3)
	{
		if (argc > 3)
			print_error(argv[0], "too many arguments", NULL, 0);
		else
			print_error(argv[0], "string not in pwd", argv[1], 0);
	}
	else
		check_request(argc, argv);
}

void	cd(int argc, char **argv)
{
	char	buf[MAXDIR];

	check_ch_dir(argc, argv);
	getcwd(buf, MAXDIR);
	set_env("OLDPWD", get_var("PWD"));
	set_env("PWD", buf);
}

