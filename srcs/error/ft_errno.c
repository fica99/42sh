/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errno.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:21:21 by filip             #+#    #+#             */
/*   Updated: 2019/07/31 14:27:52 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_perror(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	if (g_errno_f)
		pr_gen_perror();
}

void	pr_gen_perror(void)
{
	int		err;
	char	*str[4];

	str[0] = ": No such file or directory";
	str[1] = ": Cannot allocate memory";
	str[2] = ": Bad address (POSIX.1-2001)";
	str[3] = ": Permission denied";
	err = -1;
	if (g_errno_f == ENOENT)
		err = 0;
	else if (g_errno_f == ENOMEM)
		err = 1;
	else if (g_errno_f == EFAULT)
		err = 2;
	else
		err = 3;
	ft_putstr_fd(str[err], STDERR_FILENO);
}

void	print_error(char *name, char *str, char *command, int p)
{
	g_errno_f = p;
	ft_putstr_fd(name, STDERR_FILENO);
	if (str)
		ft_putstr_fd(": ", STDERR_FILENO);
	ft_perror(str);
	if (command)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(command, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	set_attr(&g_orig_mode);
	exit(EXIT_FAILURE);
}

void	print_error_withoutexit(char *name, char *str, char *command, int p)
{
	g_errno_f = p;
	ft_putstr_fd(name, STDERR_FILENO);
	if (str)
		ft_putstr_fd(": ", STDERR_FILENO);
	ft_perror(str);
	if (command)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(command, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}
