/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:18:04 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/30 20:32:37 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	make_command(char *buff, t_term *term)
{
	char	**args;
	short	i;

	if (!buff || !(*buff) || !(args = ft_strsplit(buff, ' ')))
		return ;
	i = -1;
	while (args[++i])
		args[i] = spec_symbols(args[i]);
	find_command(args, term);
	ft_free_dar(args);
}

char	*spec_symbols(char *args)
{
	char	*path;
	char	*arr;

	if (*args == '~')
	{
		if ((path = ft_getenv("HOME")))
		{
			arr = args;
			if (!(args = ft_strjoin(path, arr + 1)))
				print_error("42sh", "malloc() error", NULL, ENOMEM);
			ft_memdel((void**)&arr);
		}
	}
	if (*args == '$' && args + 1)
	{
		if ((path = ft_getenv(args + 1)))
		{
			arr = args;
			if (!(args = ft_strdup(path)))
				print_error("42sh", "malloc() error", NULL, ENOMEM);
			ft_memdel((void**)&arr);
		}
	}
	return (args);
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
		if (!S_ISREG(buf.st_mode))
			return (NULL);
		p = make_process();
		signalling();
		if (!p)
			if (execve(args[0], args, g_env) < 0)
				print_error("42sh", "execve() error", args[0], 0);
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
			print_error("42sh", "execve() error", args[0], 0);
	waitpid(p, &status, 0);
	return (SOMETHING);
}
