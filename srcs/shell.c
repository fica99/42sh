/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:55:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/02 18:48:07 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_start(void)
{
	char	*arr;

	while (RUNNING)
	{
		signalling();
		print_message();
		if (!(arr = read_prompt()))
			continue;
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
		if (ft_strcmp(args[0], "ls") == 0)
			if (execve("/bin/ls", args, env_cp) < 0)
				print_error("minishell", "execve() error", args[0], 0);
		if (ft_strcmp(args[0], "pwd") == 0)
			if (execve("/bin/pwd", args, env_cp) < 0)
				print_error("minishell", "execve error", args[0], 0);
	}
	else
		waitpid(p, &status, 0);
}

void	find_command(char **args)
{
	if (ft_strcmp(args[0], "cd") == 0)
		cd(double_arr_len(args), args);
	else if (ft_strcmp(args[0], "echo") == 0)
		echo(double_arr_len(args), args);
	else if (ft_strcmp(args[0], "env") == 0)
		env(double_arr_len(args), args);
	else if (ft_strcmp(args[0], "setenv") == 0)
		ft_setenv(double_arr_len(args), args);
	else if (ft_strcmp(args[0], "unsetenv") == 0)
		ft_unsetenv(double_arr_len(args), args);
	else if (ft_strcmp(args[0], "exit") == 0)
		exit(0);
	else if (!(ft_strcmp(args[0], "ls")) || !(ft_strcmp(args[0], "pwd")))
		exec_command(args);
	else
		print_error("minishell", "command not found", args[0], 0);

}