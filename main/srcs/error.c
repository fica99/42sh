/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:10:19 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/03 17:11:11 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

static void	ft_error(char *name, char *str, char *command, char *err)
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

int			fix_exit(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128);
	else if (WIFSTOPPED(status))
		return (130);
	else if (status == 256)
		return (1);
	else if (status == 32256)
		return (126);
	else if (status == 32512)
		return (127);
	return (status);
}

void		err_exit(char *name, char *str, char *command, char *err)
{
	ft_error(name, str, command, err);
	if (ft_strequ("permission denied", str))
		exit(126);
	else if (ft_strequ("command not found", str))
		exit(127);
	exit(EXIT_FAILURE);
}

void		err(char *name, char *str, char *command, char *err)
{
	ft_error(name, str, command, err);
}
