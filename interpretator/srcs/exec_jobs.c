/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_jobs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:23:13 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/21 13:23:15 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_job	*exec_jobs(t_job *j)
{
	t_job *last_job;

	if (!j)
		j = g_first_job;
	last_job = j;
	while (j)
	{
		last_job = j;
		launch_job(j, j->separator == T_AND ? 0 : 1);
		j = j->next;
	}
	return (last_job);
}
