/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:53:08 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/09 22:56:12 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_prompt(void)
{
	char	hostname[HOST_NAME_MAX];
	char	*path;

	gethostname(hostname, HOST_NAME_MAX);
	path = ft_strrchr(ft_getenv("PWD"), '/');
	ft_isprint(*(path + 1)) == 1 ? path = path + 1 : path;
	!ft_strcmp(ft_getenv("PWD"), ft_getenv("HOME")) ? path = "~" : path;
	ft_putstr(RED);
	ft_putchar('[');
	ft_putstr(CYAN);
	ft_putstr(ft_getenv("USER"));
	ft_putstr(RED);
	ft_putchar('@');
	ft_putstr(GREEN);
	ft_putstr(hostname);
	ft_putstr(RED);
	ft_putchar(' ');
	ft_putstr(YELLOW);
	ft_putstr(path);
	ft_putstr(RED);
	ft_putchar(']');
	ft_putstr(PURPLE);
	ft_putstr(" $> ");
	ft_putstr(STANDART);
	cord.prompt += ft_strlen(hostname) + ft_strlen(path) +
	ft_strlen(ft_getenv("USER")) + 8;
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
}
