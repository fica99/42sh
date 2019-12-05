/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 21:37:50 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/02 21:37:51 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	pwd(char **av)
{
	char	*dir;
	t_flag	no_links;

	no_links = 0;
	if (!check_flags(av, &no_links))
	{
		ft_error("42sh", av[0], PWD_USAGE, NULL);
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
