/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 23:54:15 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/26 18:20:35 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

static void	restore_fd(int *fd)
{
	if (fd[0] > -1)
	{
		if (dup2(fd[0], STDIN_FILENO) < 0)
			err_exit("42sh", "dup2() error", NULL, NOERROR);
		close(fd[0]);
	}
	if (fd[1] > -1)
	{
		if (dup2(fd[1], 1) < 0)
			err_exit("42sh", "dup2() error", NULL, NOERROR);
		close(fd[1]);
	}
	if (fd[2] > -1)
	{
		if (dup2(fd[2], STDERR_FILENO))
			err_exit("42sh", "dup2() error", NULL, NOERROR);
		close(fd[2]);
	}
}

static void	save_fd(int *fd, int **redir)
{
	fd[0] = find_dup(redir, STDIN_FILENO);
	fd[1] = find_dup(redir, STDOUT_FILENO);
	fd[2] = find_dup(redir, STDERR_FILENO);
}

int			launch_builtin(t_process *p, int no_fork)
{
	t_builtin	func;
	int			fd[3];
	char		**save_env;

	if (p->next && no_fork)
		return (-1);
	if (!(func = (t_builtin)get_hash_data(g_built_table.table,
					p->args[0], g_built_table.size)))
		return (-1);
	ft_sub(p->args);
	if (redir_handle(p) < 0)
	{
		restore_fd(fd);
		return (1);
	}
	save_fd(fd, p->fd_list);
	dup_redir(p->fd_list);
	save_env = g_env.env;
	g_env.env = get_uniq_env(p->environment);
	func(ft_darlen(p->args), p->args);
	g_env.env = save_env;
	restore_fd(fd);
	return (0);
}
