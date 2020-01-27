/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_operators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrawn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:45:06 by lcrawn            #+#    #+#             */
/*   Updated: 2020/01/27 12:45:07 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

void	set_exit_status(pid_t pid, t_job *j, int status)
{
	t_process *p;

	p = j->first_process;
	while (p)
	{
		if (p->pid == pid)
		{
			p->exit_status = status;
			return ;
		}
		p = p->next;
	}
}

int		log_check(t_job *j, t_job *last_job)
{
	t_process	*p;
	int			separator;
	int			j_amount;
	int			bad_exit;

	if (j == last_job)
		return (0);
	bad_exit = 0;
	j_amount = 0;
	separator = j->separator;
	while (j && j != last_job)
	{
		p = j->first_process;
		while (p && p->next)
			p = p->next;
		if ((p && p->exit_status) || !j->execution)
			bad_exit++;
		separator = j->next == last_job ? j->separator : separator;
		j_amount++;
		j = j->next;
	}
	if (j && ((separator == T_AND_AND && bad_exit != j_amount) ||
			(separator == T_OR_OR && bad_exit == j_amount)))
		return (0);
	return (-1);
}
