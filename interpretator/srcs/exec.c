/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:18:04 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/01 15:47:49 by lcrawn           ###   ########.fr       */
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
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
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
		cd(args);
	else if (!ft_strcmp(args[0], "echo"))
		ft_echo(len, args, g_env.env);
	else if (!ft_strcmp(args[0], "set"))
		set(len, args, g_env.env);
	else if (!ft_strcmp(args[0], "env"))
		env(len, args, g_env.env);
	else if (!ft_strcmp(args[0], "setenv"))
		set_env(len, args, g_env.env);
	else if (!ft_strcmp(args[0], "unsetenv"))
		unset_env(len, args, g_env.env);
	else if (!ft_strcmp(args[0], "hash") && len == 1)
		print_bin_table(g_bin_table.table, g_bin_table.size);
	else if (!ft_strcmp(args[0], "pwd"))
		pwd(args);
	else if (!ft_strcmp(args[0], "exit"))
		g_flags |= TERM_EXIT;
	else if (!check_bin(args, g_bin_table.table,
	g_bin_table.size) && !check_command(args))
		err("42sh", "command not found", args[0], NOERROR);
}

char	check_command(char **args)
{
	pid_t		p;
	int			status;
	struct stat	buf;

	if (!access(args[0], F_OK))
	{
		if (access(args[0], X_OK))
		{
			err("42sh", NULL, args[0], EACCES);
			return (TRUE);
		}
		if (lstat(args[0], &buf) < 0)
			err_exit("42sh", "lstat() error", NULL, NOERROR);
		if (!S_ISREG(buf.st_mode))
			return (FALSE);
		p = make_process();
		if (!p)
			if (execve(args[0], args, g_env.env) < 0)
				err_exit("42sh", "execve() error", args[0], NOERROR);
		waitpid(p, &status, 0);
		return (TRUE);
	}
	return (FALSE);
}

char	check_bin(char **args, t_hash **bin_table, short bin_table_size)
{
	pid_t			p;
	int				status;
	char			*command_path;

	if (!bin_table ||
	!(command_path = get_hash_data(bin_table, args[0], bin_table_size)))
		return (FALSE);
	p = make_process();
	if (!p)
		if (execve(command_path, args, g_env.env) < 0)
			err_exit("42sh", "execve() error", args[0], NOERROR);
	waitpid(p, &status, 0);
	return (TRUE);
}
