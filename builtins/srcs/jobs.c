/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:05:11 by lcrawn            #+#    #+#             */
/*   Updated: 2020/01/26 15:09:57 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	jobs(int argc, char **argv)
{
	if (argc == 2)
	{
		if (!ft_strcmp(argv[1], "-l"))
			do_job_notification(g_first_job, EXPAND_INFO, 0);
		else if (!ft_strcmp(argv[1], "-p"))
			do_job_notification(g_first_job, PID_INFO, 0);
		else if (ft_atoi(argv[1]) != 0)
			do_job_notification(find_job(ft_atoi(argv[1])), NO_INFO, 0);
		else
			err("42sh", "jobs", argv[1], "no such job");
	}
	else if (argc == 3)
	{
		if (!find_job(ft_atoi(argv[2])))
			err("42sh", "jobs", argv[2], "no such job");
		else if (!ft_strcmp(argv[1], "-l"))
			do_job_notification(find_job(ft_atoi(argv[2])), EXPAND_INFO, 1);
		else if (!ft_strcmp(argv[1], "-p"))
			do_job_notification(find_job(ft_atoi(argv[2])), PID_INFO, 1);
	}
	else
		do_job_notification(g_first_job, NO_INFO, 0);
}
