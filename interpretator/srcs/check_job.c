/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:40:31 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/04 20:41:35 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

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
