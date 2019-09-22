/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:21:21 by filip             #+#    #+#             */
/*   Updated: 2019/09/22 15:26:00 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_error(char *name, char *str, char *command, char *err)
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
		ft_putstr_fd(command, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	err_exit(char *name, char *str, char *command, char *err)
{
	ft_error(name, str, command, err);
	set_attr(&g_orig_mode);
	exit(EXIT_FAILURE);
}

void	err(char *name, char *str, char *command, char *err)
{
	ft_error(name, str, command, err);
}
