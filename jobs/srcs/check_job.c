/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrawn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:45:34 by lcrawn            #+#    #+#             */
/*   Updated: 2020/01/25 17:02:10 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	max_job(void)
{
	t_job *j;
	int max;

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

void mark_job_as_running (t_job *j)
{
  	t_process *p;

  	for (p = j->first_process; p; p = p->next)
    	p->stopped = 0;
}

int job_is_completed (t_job *j)
{
    t_process *p;

	//fprintf(stderr, "checking job for completion\n");
	//print_command(j->command);
    p = j->first_process;
    while (p)
    {
        if (!p->completed && !p->stopped) {
			//fprintf(stderr, "process [%s] is not completed\n", p->args[0]);
			return (0);
		}
        p = p->next;
    }
	//fprintf(stderr, "job is completed\n");
    return (1);
}

int job_is_stopped(t_job *j)
{
	t_process *p;

    //fprintf(stderr, "checking job for stopping\n");
    //print_command(j->command);
    p = j->first_process;
    while (p)
    {
		if (!p->stopped && !p->completed) {
			//fprintf(stderr, "process [%s] is not stopped\n", p->args[0]);
				return (0);
		}
		p = p->next;
    }
	//fprintf(stderr, "job is stopped\n");
	return (1);
}
