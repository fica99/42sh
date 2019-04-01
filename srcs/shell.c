/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:55:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/01 16:36:04 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_start(void)
{
	char	*arr;

	while (RUNNING)
	{
		signalling(0);
		print_message();
		arr = read_prompt();

		parse_string(arr);
	}
}

void	exec_command(char **args)
{
	pid_t	p;
	int		status;

	p = make_process();
	if (!p)
	{
		if (ft_strncmp(args[0], "ls", 2) == 0)
			execve("/bin/ls", args, env_cp);
		else if (ft_strncmp(args[0], "pwd", 3) == 0)
			execve("/bin/pwd", args, env_cp);
		signalling(1);
	}
	else
		waitpid(p, &status, 0);
}

void	find_command(char **args)
{
	if (ft_strncmp(args[0], "cd", 2) == 0)
		cd(double_arr_len(args), args);
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		echo(double_arr_len(args), args);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		env(double_arr_len(args), args);
	else if (ft_strncmp(args[0], "setenv", 6) == 0)
		ft_setenv(double_arr_len(args), args);
	else if (ft_strncmp(args[0], "unsetenv", 8) == 0)
		ft_unsetenv(double_arr_len(args), args);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		exit(0);
	else if (!(ft_strncmp(args[0], "ls", 2)) || !(ft_strncmp(args[0], "pwd", 3)))
		exec_command(args);
	else
		print_error("minishell", "command not found", args[0], 0);

}