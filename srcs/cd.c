/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/19 18:51:06 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t	cd(int argc, char **argv, char **env)
{
	char	buf[MAXDIR];

	if (argc <= 2)
	{
		if (argc == 1)
			chdir(get_var("HOME", env));
		else
			if (chdir(argv[1]) == -1)
			{
				ft_putstr("cd: no such file or directory: ");
				ft_putstr(argv[1]);
				ft_putchar('\n');
				return (-1);
			}
		getcwd(buf, MAXDIR);
		env[get_count_var("PWD", env)] = ft_strjoin("PWD=", buf);
		ft_putstr(env[6]);
	}
	else
	{
		ft_putstr("cd: no such file or directory:");
		ft_putstr(argv[1]);
		ft_putchar('\n');
	}
	return (0);
}
