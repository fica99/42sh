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

void	set_sig_def(void)
{
	signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
}

void	launch_process(t_process *p, pid_t pgid, int foreground)
{
	pid_t 	pid;

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
	if (execve(p->args[0], p->args, g_env.env) < 0)
		err_exit("42sh", "execve() error", p->args[0], NOERROR);
  	exit(1);
}
