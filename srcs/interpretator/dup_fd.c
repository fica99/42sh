/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:01:17 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/22 15:57:21 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		copy_fd(int fd, int new_fd)
{
	int	back_fd;

	if ((back_fd = dup(new_fd)) == -1)
		err_exit(g_argv[0], "dup() error", NULL, NOERROR);
	if (dup2(fd, new_fd) == -1)
		err_exit(g_argv[0], "dup2() error", NULL, NOERROR);
	return (back_fd);
}

void	restore_fd(int back_fd, int new_fd)
{
	if (dup2(back_fd, new_fd) == -1)
		err_exit(g_argv[0], "dup2() error", NULL, NOERROR);
}
