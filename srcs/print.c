/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:53:08 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/26 21:06:33 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void    ft_putstr_cord(char *str)
{
	while (str && *str)
	{
		ft_putchar_fd(*str, STDIN_FILENO);
		(g_term.x_cur)++;
		str++;
		if (g_term.x_cur > g_term.ws_col)
		{
			ft_putchar_fd('\n', STDIN_FILENO);
			g_term.x_cur = 1;
			if (g_term.y_cur >= g_term.ws_row)
				(g_term.y_start)--;
			else
				(g_term.y_cur)++;
		}
	}
}

void	print_environ(void)
{
	short	i;

	i = -1;
	while (g_term.env_cp[++i])
	{
		ft_putstr_fd(g_term.env_cp[i],STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
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
