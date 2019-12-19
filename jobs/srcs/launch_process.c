/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:37:26 by filip             #+#    #+#             */
/*   Updated: 2019/12/01 11:20:18 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	redir(int **red)
{
	while (*red)
	{
		if ((*red)[0] == -1)
			close((*red)[1]);
		dup2((*red)[0], (*red)[1]);
		red++;
	}
}

void	launch_process(t_process *p, pid_t pgid, int foreground)
{
	pid_t 	pid;
	char *fname;

	if (g_shell_is_interactive)
    {
    	pid = getpid();
    	if (pgid == 0)
			pgid = pid;
      	setpgid(pid, pgid);
      	if (foreground)
        	tcsetpgrp(g_shell_terminal, pgid);
      	set_sig_def();
    }
	if (!foreground) {
		/*close(STDOUT_FILENO);
		close(STDIN_FILENO);
		close(STDERR_FILENO);*/
	}
	if (p->next && p->next->inpipe)
		close (p->next->inpipe);
	if (p->inpipe != STDIN_FILENO)
	{
		dup2(p->inpipe, STDIN_FILENO);
		close(p->inpipe);
	}
	if (p->outpipe != STDOUT_FILENO)
	{
		dup2(p->outpipe, STDOUT_FILENO);
		close(p->outpipe);
	}
	redir(p->redir);
	if (ft_strchr(p->args[0], '/'))
		fname = p->args[0];
	else if (!(fname = (char *)get_hash_data(g_bin_table.table, p->args[0], g_bin_table.size)))
		err_exit("42sh", "command not found", p->args[0], NOERROR);
	if (execve(fname, p->args, g_env.env) < 0)
		err_exit("42sh", "execve() error", p->args[0], NOERROR);
  	exit(1);
}
