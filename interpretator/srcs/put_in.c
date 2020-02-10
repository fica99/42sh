/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 17:37:40 by lcrawn            #+#    #+#             */
/*   Updated: 2020/02/04 21:40:19 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

void		put_job_in_foreground(t_job *j, int cont)
{
	t_process *p;

	p = j->first_process;
	tcsetpgrp(g_shell_terminal, j->pgid);
	if (cont)
	{
		while (p)
		{
			ft_putstr_fd(p->args[0], STDOUT_FILENO);
			ft_putstr_fd(" ", STDOUT_FILENO);
			p = p->next;
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		tcsetattr(g_shell_terminal, TCSADRAIN, j->tmodes);
		kill(-j->pgid, SIGCONT);
	}
	wait_for_job(j);
	tcsetpgrp(g_shell_terminal, g_shell_pgid);
	tcgetattr(g_shell_terminal, j->tmodes);
	tcsetattr(g_shell_terminal, TCSADRAIN, &g_shell_tmodes);
}

void		put_job_in_background(t_job *j, int cont)
{
	t_process 	*p;
	char		*s_pid;
	char		*s_num;

	p = j->first_process;
	if (cont)
	{
		kill(-j->pgid, SIGCONT);
		return ;
	}
	while (p->next)
		p = p->next;
	s_pid = ft_itoa(p->pid);
	s_num = ft_itoa(j->num);
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(s_num, STDOUT_FILENO);
	ft_putstr_fd("] ", STDOUT_FILENO);
	ft_putstr_fd(s_pid, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	ft_strdel(&s_pid);
	ft_strdel(&s_num);
}
