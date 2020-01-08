/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:36:57 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/08 13:42:26 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_err(char *name, char *str, char *err)
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
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(RL_STOP_TRANSMIT_MODE, STDOUT_FILENO);
	reset_shell_mode();
	rl_set_mode(&g_rl.start_mode);
	exit(EXIT_FAILURE);
}
