/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrawn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:45:34 by lcrawn            #+#    #+#             */
/*   Updated: 2020/01/25 17:27:48 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		max_job(void)
{
	t_job	*j;
	int		max;

	max = 0;
	j = g_first_job;
	while (j)
	{
		if (j->num > max)
			max = j->num;
		j = j->next;
	}
	return (max + 1);
}

void	mark_job_as_running(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		p->stopped = 0;
		p = p->next;
	}
	j->notified = 0;
}

int		job_is_completed(t_job *j)
{
	t_process	*p;
	int			completed_p;
	int			all_p;

	completed_p = 0;
	all_p = 0;
	p = j->first_process;
	while (p)
	{
		all_p++;
		if (p->completed)
			completed_p++;
		p = p->next;
	}
	if (all_p == completed_p)
		return (1);
	return (0);
}

int		job_is_stopped(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		if (!p->stopped && !p->completed)
			return (0);
		p = p->next;
	}
	return (1);
}
