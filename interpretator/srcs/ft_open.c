/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:35:49 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/21 13:35:50 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	check_file_access(char *fname)
{
	if (access(fname, F_OK))
		file_err("42sh: ", "no such file or directory: ", fname, g_first_job);
	else if (access(fname, W_OK | R_OK))
		file_err("42sh: ", "permission denied: ", fname, g_first_job);
	else
		file_err("42sh: ", "failed to open/create file: ", fname, g_first_job);
	return (0);
}

int			ft_open(char *fname, int fl)
{
	int		fd;
	size_t	i;

	i = 0;
	if ((fd = open(fname, fl, PERM_MODE)) < 0)
		return (check_file_access(fname));
	return (fd);
}
