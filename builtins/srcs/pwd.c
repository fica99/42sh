/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 21:37:50 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/26 17:30:56 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	pwd(int ac, char **av)
{
	char	*dir;
	t_flag	no_links;

	(void)ac;
	no_links = 0;
	if (!check_flags(av, &no_links))
	{
		err("42sh", av[0], PWD_USAGE, NULL);
		return (-1);
	}
	if (no_links)
	{
		if (!(dir = getcwd(NULL, MAXDIR)))
			err_exit("42sh", "getcwd() error", NULL, NOERROR);
	}
	else
		dir = ft_strdup(g_curr_dir);
	ft_putstr_fd(dir, STDOUT_FILENO);
	ft_putchar('\n');
	free(dir);
	return (0);
}
