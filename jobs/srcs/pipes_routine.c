/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 17:40:53 by lcrawn            #+#    #+#             */
/*   Updated: 2020/01/26 18:20:48 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

void	close_pipes(t_process *p)
{
	if (p->inpipe != STDIN_FILENO)
		if (close(p->inpipe) < 0)
			err_exit("42sh", "close() error", NULL, NOERROR);
	if (p->outpipe != STDOUT_FILENO)
		if (close(p->outpipe) < 0)
			err_exit("42sh", "close() error", NULL, NOERROR);
}

void	open_pipe(t_process *p, int *pipes)
{
	if (p->next)
	{
		if (pipe(pipes) < 0)
			err_exit("42sh", "pipe() error", NULL, NOERROR);
		p->outpipe = pipes[1];
		p->next->inpipe = pipes[0];
	}
}
