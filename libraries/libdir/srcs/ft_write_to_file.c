/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_to_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 23:43:44 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/01 23:43:47 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdir.h"

void	ft_write_to_file(char *path, int flags, int perm, char *content)
{
	int	fd;

	if ((fd = open(path, flags, perm)) == -1)
		return ;
	ft_putstr_fd(content, fd);
	if ((close(fd)) == -1)
		return ;
}
