/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:18:04 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/19 18:14:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	make_command(char *buff)
{
	char	**args;
	short	i;

	if (!buff || !(*buff))
		return ;
	if (ft_strchr(buff, '\'') || ft_strchr(buff, '\"'))
		args = parse_quotes(buff);
	else
	{
		if (!(args = ft_strsplit(buff, ' ')))
			err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
		i = -1;
		while (args[++i])
			args[i] = spec_symbols(args[i]);
	}
	find_command(args);
	ft_free_dar(args);
}

void	find_command(char **args)
{
	int	len;

	len = ft_darlen(args);
	if (!ft_strcmp(args[0], "cd"))
		cd(len, args, g_env.env);
	else if (!ft_strcmp(args[0], "echo"))
		ft_echo(len, args, g_env.env);
	else if (!ft_strcmp(args[0], "env"))
		env(len, args, g_env.env);
	else if (!ft_strcmp(args[0], "setenv"))
		set_env(len, args, g_env.env);
	else if (!ft_strcmp(args[0], "unsetenv"))
		unset_env(len, args, g_env.env);
	else if (!ft_strcmp(args[0], "hash") && len == 1)
		print_bin_table(g_bin_table.table, g_bin_table.size);
	else if (!ft_strcmp(args[0], "history"))
		print_history(&g_history);
	else if (!ft_strcmp(args[0], "exit"))
		g_flags |= TERM_EXIT;
	else if (!check_bin(args, g_bin_table.table,
	g_bin_table.size) && !check_command(args))
		err(g_argv[0], "command not found", args[0], NOERROR);
}

char	check_command(char **args)
{
	int			status;
	struct stat	buf;

	if (!access(args[0], F_OK))
	{
		if (access(args[0], X_OK))
		{
			err(g_argv[0], NULL, args[0], EACCES);
			return (TRUE);
		}
		if (lstat(args[0], &buf) < 0)
			err_exit(g_argv[0], "lstat() error", NULL, NOERROR);
		if (!S_ISREG(buf.st_mode))
			return (FALSE);
		g_chld_pid = make_process();
		if (g_chld_pid == 0)
		{
			signalling_chld();
			if (execve(args[0], args, g_env.env) < 0)
				err_exit(g_argv[0], "execve() error", args[0], NOERROR);
		}
		else
		{
			signalling();
			do
			{
				waitpid(g_chld_pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSTOPPED(status));
				
		}
		return (TRUE);
	}
	return (FALSE);
}

char	check_bin(char **args, t_hash **bin_table, short bin_table_size)
{
	int				status;
	char			*command_path;

	if (!bin_table ||
	!(command_path = get_hash_data(bin_table, args[0], bin_table_size)))
		return (false);
	g_chld_pid = make_process();
	if (g_chld_pid == 0)
	{
		//signalling_chld();
		if (execve(command_path, args, g_env.env) < 0)
			err_exit(g_argv[0], "execve() error", args[0], NOERROR);
	}
	else
	{
		signalling();
		waitpid(g_chld_pid, &status, 0);
	}
	return (true);
}
