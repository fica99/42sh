/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/20 21:08:43 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

# define MAXDIR 256

static short	get_count_var(char *arr, char **env)
{
	uint8_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], arr, ft_strlen(arr)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static char	*get_var(char *arr, char **env)
{
	return (&(env[get_count_var(arr, env)][ft_strlen(arr) + 1]));
}

static uint8_t	check_request(int argc, char  **argv, char **env)
{
	if (argc == 1)
		argv[1] = (get_var("HOME", env));
	if (ft_strcmp(argv[1], "-") == 0)
		argv[1] = get_var("OLDPWD", env);
	if (chdir(argv[1]) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putstr(argv[1]);
		ft_putchar('\n');
		exit(-1);
	}
	return (1);	
}

static uint8_t	check_ch_dir(int argc , char **argv, char **env)
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
		check_request(argc, argv, env);
	}
	return (1);
}

uint8_t	cd(int argc, char **argv, char **env)
{
	char	buf[MAXDIR];

	check_ch_dir(argc, argv, env);
	getcwd(buf, MAXDIR);
	env[get_count_var("PWD", env)] = ft_strjoin("PWD=", buf);
	ft_putstr(env[6]);
	return (0);
}