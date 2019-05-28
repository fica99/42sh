/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errno.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:21:21 by filip             #+#    #+#             */
/*   Updated: 2019/05/28 19:29:16 by aashara-         ###   ########.fr       */
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
	char	*str[3];

	str[0] = ": No such file or directory";
	str[1] = ": Cannot allocate memory";
	str[2] = ": Permission denied";
	err = -1;
	if (g_errno_f == ENOENT)
		err = 0;
	else if (g_errno_f == ENOMEM)
		err = 1;
	else
		err = 2;
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
