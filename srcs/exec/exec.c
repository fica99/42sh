/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:18:04 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/27 23:45:42 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	find_command(char **args, t_hash **hash_table, short hash_table_size,
t_history *history)
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
	else if (ft_strcmp(args[0], "hash") == 0 && double_arr_len(args) == 1)
		print_hash_table(hash_table, hash_table_size);
	 else if (ft_strcmp(args[0], "history") == 0)
		print_history(history->history_buff);
	else if (ft_strcmp(args[0], "exit") == 0)
	{
		g_flags |= TERM_EXIT;
		return ;
	}
	else if (!check_command(args) && !exec_command(args, hash_table,
	hash_table_size))
		print_error_withoutexit("42sh", "command not found", args[0], 0);
}

char	*check_command(char **args)
{
	pid_t		p;
	int			status;
	struct stat	buf;

	if (!access(args[0], F_OK))
	{
		if (access(args[0], X_OK))
		{
			print_error_withoutexit("42sh", NULL, args[0], 13);
			return (SOMETHING);
		}
		if (lstat(args[0], &buf) < 0)
			print_error("42sh", "lstat() error", NULL, 0);
		if (!ft_strchr(args[0], '/') || !S_ISREG(buf.st_mode))
			return (NULL);
		p = make_process();
		signalling();
		if (!p)
			if (execve(args[0], args, g_term.env_cp) < 0)
				print_error("42sh", "execve() error", args[0], 0);
		waitpid(p, &status, 0);
		return (SOMETHING);
	}
	return (NULL);
}

char	*exec_command(char **args, t_hash **hash_table, short hash_table_size)
{
	pid_t			p;
	int				status;
	t_hash			*hash;

	if (!hash_table)
		return (NULL);
	hash = hash_table[hash_index(hashing(args[0]), hash_table_size)];
	while (hash)
	{
		if (!ft_strcmp(hash->name, args[0]))
			break ;
		hash = hash->next;
	}
	if (!hash)
		return (NULL);
	p = make_process();
	signalling();
	if (!p)
		if (execve(hash->path, args, g_term.env_cp) < 0)
			print_error("42sh", "execve() error", args[0], 0);
	waitpid(p, &status, 0);
	return (SOMETHING);
}
