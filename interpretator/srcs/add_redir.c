/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:20:57 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/21 13:20:58 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	add_redir(t_process *curr_proc, int fd0, int fd1)
{
	size_t	i;
	int		**tmp;
	int		*fd;

	i = 0;
	tmp = curr_proc->fd_list;
	if (!(fd = (int *)malloc(sizeof(int) * 2)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	fd[0] = fd0;
	fd[1] = fd1;
	while (tmp[i])
	{
		if (i >= curr_proc->redir_size - 1)
		{
			curr_proc->redir_size *= 2;
			if (!(tmp = ft_realloc(curr_proc->fd_list, curr_proc->redir_size / 2
			* sizeof(int *), curr_proc->redir_size * sizeof(int *))))
				err_exit("42sh", "malloc() error", NULL, NOERROR);
			curr_proc->fd_list = tmp;
		}
		i++;
	}
	tmp[i] = fd;
}
