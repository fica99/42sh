/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 17:33:35 by lcrawn            #+#    #+#             */
/*   Updated: 2020/01/26 18:20:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

void	print_command(char **command)
{
	int i;

	i = 0;
	while (command[i])
	{
		ft_putstr_fd(command[i], STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	format_job_info(t_job *j, const char *status, int options)
{
	if (options == NO_INFO)
		no_info_output(j->num, j->num == max_job() - 1 ? '+' : '-',
				status, j->command);
	else if (options == PID_INFO)
		pid_info_output(j->pgid);
	else if (options == EXPAND_INFO)
	{
		expand_info_output(j->num,
				j->num == max_job() - 1 ? '+' : '-', j->pgid, status);
		print_command(j->command);
	}
}

void	ft_completion_error(char *name, char *str, char **command, char *err)
{
	ft_putstr_fd(name, STDERR_FILENO);
	if (str)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
	}
	if (err)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(err, STDERR_FILENO);
	}
	if (command)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		print_command(command);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	completion_err(char *name, char *str, char **command, char *err)
{
	ft_completion_error(name, str, command, err);
}
