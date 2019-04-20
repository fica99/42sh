/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:53:08 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/20 13:39:02 by filip            ###   ########.fr       */
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


void	shell_prompt(void)
{
	char	*path;
	char	hostname[HOST_NAME_MAX];

	gethostname(hostname, HOST_NAME_MAX);
	RED(STDERR_FILENO);
	ft_putchar_fd('[', STDERR_FILENO);
	CYAN(STDIN_FILENO);
	ft_putstr_fd(ft_getenv("USER"), STDIN_FILENO);
	RED(STDIN_FILENO);
	ft_putchar_fd('@', STDIN_FILENO);
	GREEN(STDIN_FILENO);
	ft_putstr_fd(hostname, STDIN_FILENO);
	RED(STDIN_FILENO);
	ft_putchar_fd(' ', STDIN_FILENO);
	YELLOW(STDIN_FILENO);
	path = check_path();
	ft_putstr_fd(path, STDIN_FILENO);
	RED(STDIN_FILENO);
	ft_putchar_fd(']', STDIN_FILENO);
	PURPLE(STDIN_FILENO);
	ft_putstr_fd(" $> ", STDIN_FILENO);
	STANDART(STDIN_FILENO);
	cord.prompt = ft_strlen(path) + ft_strlen(ft_getenv("USER")) +
		ft_strlen(hostname) + 8;
	cord.x_cur = cord.prompt;
	cord.y_cur = 0;
}

void    ft_putstr_cord(char *str)
{
	while (str && *str)
    {
		if (cord.x_cur > cord.ws_col - 1)
		{
			ft_putchar('\n');
			cord.x_cur = 0;
			(cord.y_cur)++;
		}
		ft_putchar_fd(*str, STDIN_FILENO);
        (cord.x_cur)++;
        str++;
    }
}

void	print_environ(void)
{
	short	i;

	i = -1;
	while (env_cp[++i])
	{
		ft_putstr(env_cp[i]);
		ft_putchar('\n');
	}
}

void	print_error_withoutexit(char *name, char *str, char *command, int p)
{
	errno_f = p;
	ft_putstr(name);
	if (str)
		ft_putstr(": ");
	ft_perror(str);
	if (command)
	{
		ft_putstr(": ");
		ft_putstr(command);
	}
	ft_putchar('\n');
}
