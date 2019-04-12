/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:55:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/12 16:53:34 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_start(void)
{
	char		*arr;

	set_input_mode();
	while (RUNNING)
	{
		signalling();
		cord.prompt = 0;
		shell_prompt();
		arr = read_prompt();
		parse_string(arr);
		ft_memdel((void**)&arr);
	}
}

char	*exec_command(char **args)
{
	pid_t	p;
	int		status;
	char	**path;
	uint8_t	i;
	char	*file_path;

	if (!(path = ft_strsplit(ft_getenv("PATH"), ':')))
		print_error("minishell", "malloc() error", NULL, ENOMEM);
	i = -1;
	while (path[++i])
	{
		if (!(file_path = ft_strjoin(ft_strcat(path[i], "/"), args[0])))
			print_error("minishell", "malloc() error", NULL, ENOMEM);
		if (!access(file_path, F_OK))
		{
			p = make_process();
			if (!p)
			{
				if (execve(file_path, args, env_cp) < 0)
					print_error("minishell", "execve() error", args[0], 0);
			}
			else
			{
				waitpid(p, &status, 0);
				ft_memdel((void**)&file_path);
				free_double_arr(path);
				return ("1");
			}
		}
		ft_memdel((void**)&file_path);
	}
	free_double_arr(path);
	return (NULL);
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
	{
		free_double_arr(env_cp);
		reset_input_mode();
		exit(0);
	}
	else if (!exec_command(args))
		print_error_withoutexit("minishell", "command not found", args[0], 0);
}