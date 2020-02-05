/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:44:50 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/05 14:17:40 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

int	l_redir(t_lex_tkn **list, t_process *curr_proc, int io_number)
{
	int fd_w;

	io_number = io_number < 0 ? 0 : io_number;
	list++;
	if ((fd_w = ft_open((*list)->value, O_RDONLY)) < 0)
		return (-1);
	add_redir(curr_proc, fd_w, io_number);
	return (0);
}

int	g_redir(t_lex_tkn **list, t_process *curr_proc, int io_number)
{
	int fl;
	int fd_w;

	fl = (*list)->type == T_GREATER ? O_RDWR | O_CREAT | O_TRUNC :
											O_RDWR | O_CREAT | O_APPEND;
	if (io_number < 0)
		io_number = 1;
	++list;
	if ((fd_w = ft_open((*list)->value, fl)) < 0)
		return (-1);
	add_redir(curr_proc, fd_w, io_number);
	return (0);
}
