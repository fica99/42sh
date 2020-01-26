/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_aggr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:25:03 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/26 18:12:03 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static int	get_fd(char *str)
{
	int fd;
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
	}
	fd = ft_atoi(str);
	return (fd);
}

int			find_fd(int **redir, int fd)
{
	while (*redir)
	{
		if ((*redir)[1] == fd)
			return (0);
		redir++;
	}
	return (-1);
}

int			g_aggr(t_lex_tkn **list, t_process *curr_proc, int io_number)
{
	int fd_w;

	io_number = io_number > 0 ? io_number : 1;
	++list;
	if (!ft_strcmp((*list)->value, "-"))
		fd_w = -1;
	else if ((fd_w = get_fd((*list)->value)) < 0)
		return (g_redir(--list, curr_proc, io_number));
	else if (fd_w > 2 && find_fd(curr_proc->fd_list, fd_w) < 0)
	{
		err("42sh", (*list)->value, NULL, "Bad file descriptor");
		return (-1);
	}
	add_redir(curr_proc, fd_w, io_number);
	return (0);
}

int			l_aggr(t_lex_tkn **list, t_process *curr_proc, int io_number)
{
	int fd_w;

	io_number = io_number > 0 ? io_number : 0;
	++list;
	if (!ft_strcmp((*list)->value, "-"))
		fd_w = -1;
	else if ((fd_w = get_fd((*list)->value)) < 0)
	{
		err("42sh", (*list)->value, NULL, "ambiguous redirect");
		return (-1);
	}
	else if (fd_w > 2 && find_fd(curr_proc->fd_list, fd_w) < 0)
	{
		err("42sh", (*list)->value, NULL, "Bad file descriptor");
		return (-1);
	}
	add_redir(curr_proc, fd_w, io_number);
	return (0);
}
