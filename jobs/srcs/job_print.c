/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrawn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 17:33:35 by lcrawn            #+#    #+#             */
/*   Updated: 2020/01/25 17:34:28 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	print_command(char **command)
{
	int i;

	i = 0;
	while (command[i])
	{
		fprintf(stderr, "%s ", command[i]);
		i++;
	}
	fprintf(stderr, "\n");
}

void	format_job_info(t_job *j, const char *status, int options)
{
	if (options == NO_INFO)
	{
		fprintf(stderr, "[%d]%c %s: ",
				j->num, j->num == max_job() - 1 ? '+' : '-', status);
		print_command(j->command);
	}
	else if (options == PID_INFO)
		fprintf(stderr, "%ld\n", (long)j->pgid);
	else if (options == EXPAND_INFO)
	{
		fprintf(stderr, "[%d]%c %ld %s: ",
				j->num, j->num == max_job() - 1 ? '+' : '-', (long)j->pgid,
				status);
		print_command(j->command);
	}
}
