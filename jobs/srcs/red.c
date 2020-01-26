/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:04:34 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/26 18:20:55 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

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
