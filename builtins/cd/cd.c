/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/25 21:51:59 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
# include <dirent.h>
# include <unistd.h>

# define MAXDIR 4097

static uint8_t	check_request(int argc, char  **argv, char **environ)
{
	if (argc == 1 || ft_strcmp(argv[1], "--") == 0)
		argv[1] = (get_var("HOME", environ));
	if (ft_strcmp(argv[1], "-") == 0)
		argv[1] = get_var("OLDPWD", environ);
	if (chdir(argv[1]) == -1)
	{
		perror("cd: ");
		//ft_putstr("cd: no such file or directory: ");
		//ft_putstr(argv[1]);
		//ft_putchar('\n');
		exit(1);
	}
	return (1);	
}

static uint8_t	check_ch_dir(int argc , char **argv, char **environ)
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
		check_request(argc, argv, environ);
	return (1);
}

uint8_t	cd(int argc, char **argv, char **environ)
{
	char	buf[MAXDIR];

	check_ch_dir(argc, argv, environ);
	getcwd(buf, MAXDIR);
	set_env(environ, "OLDPWD", get_var("PWD", environ));
	set_env(environ, "PWD", buf);
	return (0);
}

int		main(int argc, char **argv, char **environ)
{
	cd(argc, argv, environ);
	return (0);
}
