/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/25 16:04:15 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **environ)
{
	pid_t	p;
	int		status;
	
	(void)argc;
	(void)argv;
	env_cp = copy_double_arr(environ);
	while (RUNNING)
	{
		ft_putstr(get_var("PWD", env_cp));
		ft_putchar(':');
		p = fork();
		if (!p)
		{
			execle("./bin/ls", "./ls", env_cp);
			exit(0);
		}
		else if (p == -1)
			exit(1);
		else
		{
			wait(&status);
		}
	}
	free_double_arr(env_cp);
	return (0);
}
