/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:54:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/28 21:04:52 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term.h"

void	parse_string(void)
{
	char	*new_command;
	char	*buf;

	if (!g_term.buffer)
		return;
	buf = g_term.buffer;
	while ((new_command = ft_strchr(buf, ';')) != NULL)
	{
		if (buf == new_command)
		{
			buf++;
			continue;
		}
		else
			*new_command = '\0';
		make_command(buf);
		buf = ++new_command;
	}
	make_command(buf);
}

void	make_command(char *buf)
{
	char	**args;

	args = NULL;
	if (*buf != '\0')
	{
		if ((args = ft_strsplit(buf, ' ')))
		{
			args = spec_symbols(args);
			find_command(args);
			free_double_arr(args);
		}
	}
}

char	**spec_symbols(char **args)
{
	short	i;
	char	*path;

	i = -1;
	while (args[++i])
	{
		if (!(ft_strcmp(args[i], "~")))
			if ((path = ft_getenv("HOME")))
				if (!(args[i] = ft_strdup(path)))
					print_error("echo", "malloc() error", NULL, ENOMEM);
		if (!(ft_strncmp(args[i], "$", 1)) && ft_strlen(args[i]) != 1)
			if ((path = ft_getenv(&(args[i][1]))))
				if (!(args[i] = ft_strdup(path)))
					print_error("echo", "malloc() error", NULL, ENOMEM);
	}
	return (args);
}

void	find_command(char **args)
{
	if (ft_strcmp(args[0], "cd") == 0)
		cd(double_arr_len(args), args, g_term.env_cp);
	else if (ft_strcmp(args[0], "echo") == 0)
		echo(double_arr_len(args), args, g_term.env_cp);
	else if (ft_strcmp(args[0], "env") == 0)
		env(double_arr_len(args), args, g_term.env_cp);
	else if (ft_strcmp(args[0], "setenv") == 0)
		set_env(double_arr_len(args), args, g_term.env_cp);
	else if (ft_strcmp(args[0], "unsetenv") == 0)
		ft_unsetenv(double_arr_len(args), args, g_term.env_cp);
	else if (ft_strcmp(args[0], "exit") == 0)
		exit(EXIT_SUCCESS);
	else if (!check_command(args)  && !exec_command(args))
		print_error_withoutexit("minishell", "command not found", args[0], 0);
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
		if (!ft_strchr(args[0], '/') || !S_ISREG(buf.st_mode))
			return (NULL);
		p = make_process();
		if (!p)
		{
			if (execve(args[0], args, g_term.env_cp) < 0)
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
				if (execve(file_path, args, g_term.env_cp) < 0)
					print_error("minishell", "execve() error", args[0], 0);
			}
			else
			{
				waitpid(p, &status, 0);
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


