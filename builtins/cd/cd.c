/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/22 16:36:15 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

# define MAXDIR 256

static uint8_t	check_request(int argc, char  **argv, char **environ)
{
	if (argc == 1)
		argv[1] = (get_var("HOME", environ));
	if (ft_strcmp(argv[1], "-") == 0)
		argv[1] = get_var("OLDPWD", environ);
	if (chdir(argv[1]) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putstr(argv[1]);
		ft_putchar('\n');
		exit(-1);
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
		exit (-1);
	}
	else
	{
		check_request(argc, argv, environ);
	}
	return (1);
}

uint8_t	cd(int argc, char **argv, char **environ)
{
	char	buf[MAXDIR];

	check_ch_dir(argc, argv, environ);
	getcwd(buf, MAXDIR);
	environ[get_count_var("PWD", environ)] = ft_strjoin("PWD=", buf);
//	ft_putstr(get_var("PWD", environ));
	return (0);
}