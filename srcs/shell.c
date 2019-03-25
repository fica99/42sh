/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:55:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/25 21:58:54 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_start(void)
{
	pid_t	p;
	int		status;
	
	while (RUNNING)
	{
		print_message();
    	p = fork();
		if (p < 0)
		{
			perror("Fork() error");
			exit(1);
		}
		if (p)
			waitpid(p, &status, 0);
		else
			read_prompt();
	}
}

void	find_command(char *args)
{
	char	*path;
	
	if (ft_strncmp(args[0], "ls", 2) == 0)
		path = ft_strdup("/bin/ls");
	else if (ft_strncmp(args[0], "cd", 2) == 0)
		path = ft_strdup("/bin/cd");
	execve(path, args, env_cp);
}