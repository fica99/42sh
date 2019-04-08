/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:53:08 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/08 16:00:29 by aashara-         ###   ########.fr       */
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
	!ft_strcmp(ft_getenv("PWD"), ft_getenv("HOME")) ? ft_putchar('~') : ft_putstr(path);
	ft_putstr(RED);
	ft_putchar(']');
	ft_putstr(PURPLE);
	ft_putstr(" $> ");
	ft_putstr(STANDART);
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

/*void	ft_putstr_print(char *arr, t_tc *tc)
{
	int		i;

	i = 0;
	tc = NULL;
	while (arr[i])
	{
		if (ft_isprint(arr[i]))
			ft_putchar(arr[i]);
		else if (arr[i] == 27)
		{
			if (ft_strstr(arr, RIGHT) && arr[i + 3])
				ft_putstr(RIGHT);
			else if (ft_strstr(arr, LEFT) && (cord.x != 0 && cord.y == 0))
				ft_putstr(LEFT);
			i += 2;
			(cord.x) += 2;
		}
		i++;
		(cord.x)++;
	}
}*/