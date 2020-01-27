/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprintf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrawn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:11:21 by lcrawn            #+#    #+#             */
/*   Updated: 2020/01/27 12:11:22 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

void	no_info_output(int num, char c, const char *status, char **command)
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

void	pid_info_output(pid_t pid)
{
	char *s_pid;

	s_pid = ft_itoa((long)pid);
	ft_putstr_fd(s_pid, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_strdel(&s_pid);
}

void	expand_info_output(int num, char c, pid_t pid, const char *status)
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
