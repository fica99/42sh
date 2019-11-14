/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:37:26 by filip             #+#    #+#             */
/*   Updated: 2019/10/19 18:14:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

pid_t	make_process(void)
{
	pid_t	p;

	p = fork();
	if (p < 0)
		err_exit("minishell", "fork() error", NULL, NOERROR);
	return (p);
}

void	launch_process(t_process *p, pid_t pgid, int foreground)
{
	pid_t 	pid;
	struct 	sigaction usr_action;

	if (g_shell_is_interactive)
    {
    	pid = getpid();
    	if (pgid == 0)
			pgid = pid;
      	setpgid(pid, pgid);
      	if (foreground)
        	tcsetpgrp(g_shell_terminal, pgid);
      	sigaction_set(SIG_DFL, &usr_action);
    }
	if (execve(p->args[0], p->args, g_env.env) < 0)
		err_exit(g_argv[0], "execve() error", p->args[0], NOERROR);
  	exit(1);
}