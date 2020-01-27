/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_jobs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara <aashara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:23:13 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/26 20:59:15 by aashara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

void	exec_jobs(void)
{
	t_job *j;
	t_job *first_job;

	if (!g_last_job || !g_last_job->next)
		j = g_first_job;
	else
	{
		g_last_job = g_last_job->next;
		j = g_last_job;
	}
	first_job = j;
	while (j)
	{
		g_last_job = j;
		if (!log_check(first_job, j) && !job_is_completed(j) && !job_is_stopped(j))
		{
			j->execution = 1;
			launch_job(j, j->separator == T_AND ? 0 : 1);
		}
		else
			j->execution = 0;
		j = j->next;
	}
}
