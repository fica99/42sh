/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:35:49 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/24 13:38:25 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	check_file_access(char *fname)
{
	if (access(fname, F_OK))
		ft_error("42sh", "no such file or directory", NULL, fname);
	else if (access(fname, W_OK | R_OK))
		ft_error("42sh", "permission denied", NULL, fname);
	else
		ft_error("42sh", "failed to open/create file", NULL, fname);
}

int			ft_open(char *fname, int fl)
{
	int		fd;

	if ((fd = open(fname, fl, PERM_MODE)) < 0)
		check_file_access(fname);
	return (fd);
}
