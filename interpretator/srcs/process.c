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
      /* Put the process into the process group and give the process group
        the terminal, if appropriate.
        This has to be done both by the shell and in the individual
        child processes because of potential race conditions.  */
    	pid = getpid();
    	if (pgid == 0)
			pgid = pid;
      	setpgid(pid, pgid);
      	if (foreground)
        	tcsetpgrp(g_shell_terminal, pgid);
      	/* Set the handling for job control signals back to the default.  */
      	sigaction_set(SIG_DFL, &usr_action);
    }
  	/* Exec the new process.  Make sure we exit.  */
  	execvp (p->argv[0], p->argv);
  	perror ("execvp");
  	exit (1);
}