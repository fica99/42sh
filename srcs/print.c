/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:53:08 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/15 22:59:47 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_prompt(void)
{
	char	*path;
	char	hostname[HOST_NAME_MAX];

	gethostname(hostname, HOST_NAME_MAX);
	RED;
	ft_putchar('[');
	CYAN;
	ft_putstr(ft_getenv("USER"));
	RED;
	ft_putchar('@');
	GREEN;
	ft_putstr(hostname);
	RED;
	ft_putchar(' ');
	YELLOW;
	path = check_path();
	ft_putstr(path);
	RED;
	ft_putchar(']');
	PURPLE;
	ft_putstr(" $> ");
	STANDART;
	cord.prompt = ft_strlen(path) + ft_strlen(ft_getenv("USER")) +
		ft_strlen(hostname) + 8;
	cord.x_cur = cord.prompt;
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

void	print_error(char *name, char *str, char *command, int p)
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
	exit(EXIT_FAILURE);
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
