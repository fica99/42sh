/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:55:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/14 14:46:41 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_start(void)
{
	char		*arr;

	while (RUNNING)
	{
		signalling();
		if (g_flags & SHELL_SIGINT)
			g_flags &= ~SHELL_SIGINT;
		else
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

	path = ft_strsplit(ft_getenv("PATH"), ':');
	i = -1;
	while (path[++i])
	{
		if (!(file_path = ft_strjoin(ft_strcat(path[i], "/"), args[0])))
			print_error("minishell", "malloc() error", NULL, ENOMEM);
		if (!access(file_path, F_OK | X_OK) && !ft_strcmp(ft_strrchr(file_path, '/') + 1, args[0]))
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
				if (g_flags & SHELL_SIGQUIT)
				{
					g_flags &= ~SHELL_SIGQUIT;
					ft_putchar('\n');
				}
				ft_memdel((void**)&file_path);
				free_double_arr(path);
				return (SOMETHING);
			}
		}
		ft_memdel((void**)&file_path);
	}
	if (path)
		free_double_arr(path);
	return (NULL);
}

char	*check_command(char **args)
{
	pid_t		p;
	int			status;
	struct stat	buf;

	if (!access(args[0], F_OK | X_OK))
	{
		if (lstat(args[0], &buf) < 0)
			print_error("minishell", "lstat() error", NULL, 0);
		if (!S_ISREG(buf.st_mode))
			return (SOMETHING);
		p = make_process();
		if (!p)
		{
			if (execve(args[0], args, env_cp) < 0)
				print_error("minishell", "execve() error", args[0], 0);
		}
		else
		{
			waitpid(p, &status, 0);
			return (SOMETHING);
		}
	}
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
		exit(EXIT_SUCCESS);
	}
	else if (!check_command(args)  && !exec_command(args))
		print_error_withoutexit("minishell", "command not found", args[0], 0);
}