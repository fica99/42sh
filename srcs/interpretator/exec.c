/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:18:04 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/14 19:59:06 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	make_command(char *buff, t_term *term)
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
	find_command(args, term);
	ft_free_dar(args);
}

void	find_command(char **args, t_term *term)
{
	if (ft_strcmp(args[0], "cd") == 0)
		cd(ft_darlen(args), args, g_env);
	else if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(ft_darlen(args), args, g_env);
	else if (ft_strcmp(args[0], "env") == 0)
		env(ft_darlen(args), args, g_env);
	else if (ft_strcmp(args[0], "setenv") == 0)
		set_env(ft_darlen(args), args, g_env);
	else if (ft_strcmp(args[0], "unsetenv") == 0)
		ft_unsetenv(ft_darlen(args), args, g_env);
	else if (ft_strcmp(args[0], "hash") == 0 && ft_darlen(args) == 1)
		print_hash_table(term->hash_table, term->hash_table_size);
	else if (ft_strcmp(args[0], "history") == 0)
		print_history(&term->history);
	else if (ft_strcmp(args[0], "exit") == 0)
	{
		g_flags |= TERM_EXIT;
		return ;
	}
	else if (!check_bin(args, term->hash_table,
	term->hash_table_size) && !check_command(args))
		err("42sh", "command not found", args[0], NOERROR);
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
			err("42sh", NULL, args[0], EACCES);
			return (SOMETHING);
		}
		if (lstat(args[0], &buf) < 0)
			err_exit("42sh", "lstat() error", NULL, NOERROR);
		if (!S_ISREG(buf.st_mode))
			return (NULL);
		p = make_process();
		signalling();
		if (!p)
			if (execve(args[0], args, g_env) < 0)
				err_exit("42sh", "execve() error", args[0], NOERROR);
		waitpid(p, &status, 0);
		return (SOMETHING);
	}
	return (NULL);
}

char	*check_bin(char **args, t_hash **hash_table, short hash_table_size)
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
		if (execve(hash->path, args, g_env) < 0)
			err_exit("42sh", "execve() error", args[0], NOERROR);
	waitpid(p, &status, 0);
	return (SOMETHING);
}
