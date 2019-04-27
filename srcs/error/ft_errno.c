/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errno.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:21:21 by filip             #+#    #+#             */
/*   Updated: 2019/04/28 00:11:28 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term.h"

void ft_perror(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	if (errno_f)
		pr_gen_perror();
}

void pr_gen_perror(void)
{
	int err;
	char *str[] = {
			": No such file or directory",
			": Cannot allocate memory",
			": Permission denied",
	};
	err = -1;
	if (errno_f == ENOENT)
		err = 0;
	else if (errno_f == ENOMEM)
		err = 1;
	else
		err = 2;
	ft_putstr_fd(str[err], STDERR_FILENO);
}

void	print_error(char *name, char *str, char *command, int p)
{
	errno_f = p;
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
	errno_f = p;
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
