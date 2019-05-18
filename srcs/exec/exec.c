/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:18:04 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/18 17:13:54 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	find_command(char **args)
{
	if (ft_strcmp(args[0], "cd") == 0)
		cd(double_arr_len(args), args, g_term.env_cp);
	else if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(double_arr_len(args), args, g_term.env_cp);
	else if (ft_strcmp(args[0], "env") == 0)
		env(double_arr_len(args), args, g_term.env_cp);
	else if (ft_strcmp(args[0], "setenv") == 0)
		set_env(double_arr_len(args), args, g_term.env_cp);
	else if (ft_strcmp(args[0], "unsetenv") == 0)
		ft_unsetenv(double_arr_len(args), args, g_term.env_cp);
	else if (ft_strcmp(args[0], "exit") == 0)
	{
		g_flags |= TERM_EXIT;
		return;
	}
	else if (!check_command(args)  && !exec_command(args))
		print_error_withoutexit("42sh", "command not found", args[0], 0);
}

char	*check_command(char **args)
{
	pid_t		p;
	int			status;
	struct stat	buf;

	if (!access(args[0], F_OK | X_OK))
	{
		if (lstat(args[0], &buf) < 0)
			print_error("42sh", "lstat() error", NULL, 0);
		if (!ft_strchr(args[0], '/') || !S_ISREG(buf.st_mode))
			return (NULL);
		p = make_process();
		if (!p)
		{
			if (execve(args[0], args, g_term.env_cp) < 0)
				print_error("42sh", "execve() error", args[0], 0);
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

	if (!(path = ft_strsplit(ft_getenv("PATH"), ':')))
		return (NULL);
	i = -1;
	while (path[++i])
	{
		if (!(file_path = ft_strjoin(ft_strcat(path[i], "/"), args[0])))
			print_error("42sh", "malloc() error", NULL, ENOMEM);
		if (!access(file_path, F_OK | X_OK) && !ft_strcmp(ft_strrchr(file_path, '/') + 1, args[0]))
		{
			p = make_process();
			if (!p)
			{
				if (execve(file_path, args, g_term.env_cp) < 0)
					print_error("42sh", "execve() error", args[0], 0);
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

