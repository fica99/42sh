/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 17:33:35 by lcrawn            #+#    #+#             */
/*   Updated: 2020/02/05 16:29:41 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_command(char **command)
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

static void	no_info_output(int num, char c, const char *status, char **command)
{
	char *s_num;

	s_num = ft_itoa(num);
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(s_num, STDOUT_FILENO);
	ft_putstr_fd("]", STDOUT_FILENO);
	ft_putchar_fd(c, STDOUT_FILENO);
	ft_putstr_fd(" ", STDOUT_FILENO);
	ft_putstr_fd(status, STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	print_command(command);
	ft_strdel(&s_num);
}

static void	pid_info_output(pid_t pid)
{
	char *s_pid;

	s_pid = ft_itoa((long)pid);
	ft_putstr_fd(s_pid, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_strdel(&s_pid);
}

static void	expand_info_output(int num, char c, pid_t pid, const char *status)
{
	char *s_num;
	char *s_pid;

	s_num = ft_itoa(num);
	s_pid = ft_itoa((long)pid);
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(s_num, STDOUT_FILENO);
	ft_putstr_fd("]", STDOUT_FILENO);
	ft_putchar_fd(c, STDOUT_FILENO);
	ft_putstr_fd(" ", STDOUT_FILENO);
	ft_putstr_fd(s_pid, STDOUT_FILENO);
	ft_putstr_fd(" ", STDOUT_FILENO);
	ft_putstr_fd(status, STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	ft_strdel(&s_num);
	ft_strdel(&s_pid);
}

void		format_job_info(t_job *j, const char *status, int options)
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
