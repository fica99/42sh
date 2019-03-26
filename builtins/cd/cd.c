/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/26 19:13:25 by filip            ###   ########.fr       */
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
	if (chdir(argv[1]) == -1)
	{
		perror("cd: chdir() error");
		//ft_putstr("cd: no such file or directory: ");
		//ft_putstr(argv[1]);
		//ft_putchar('\n');
		exit(1);
	}
}

void	check_ch_dir(int argc , char **argv)
{
	if (argc >= 3)
	{
		if (argc > 3)
			ft_putstr("cd: too many arguments\n");
		else
		{
			ft_putstr("cd: string not in pwd: ");
			ft_putstr(argv[1]);
			ft_putchar('\n');
		}
		exit(1);
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
	exit(0);
}

