/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 22:26:50 by jijerde           #+#    #+#             */
/*   Updated: 2020/02/15 22:28:37 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

void	clean_all_err_processes(t_job *j)
{
	t_process *p;

	p = j->first_process;
	j->execution = 0;
	while (p)
	{
		p->completed = 1;
		cls_redir(p->fd_list);
		close_pipes(p);
		p = p->next;
	}
}

void	clean_proc(t_process *p, t_job *j, int pid)
{
	cls_redir(p->fd_list);
	p->pid = pid;
	if (!j->pgid)
		j->pgid = pid;
	setpgid(pid, j->pgid);
	close_pipes(p);
}
