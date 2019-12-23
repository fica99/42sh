/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:04:34 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/21 16:04:35 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		find_dup(int **redir, int fd)
{
	int fd2;

	while (*redir)
	{
		if ((*redir)[1] == fd)
		{
			if ((fd2 = dup(fd)) < 0)
				err_exit("42sh", "dup() error", NULL, NOERROR);
			return (fd2);
		}
		redir++;
	}
	return (-1);
}

pid_t	make_process(void)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		err_exit("42sh", "dup() error", NULL, NOERROR);
	return (pid);
}

void	redir(int **red)
{
	while (*red)
	{
		if ((*red)[0] == -1)
			close((*red)[1]);
		dup2((*red)[0], (*red)[1]);
		red++;
	}
}
