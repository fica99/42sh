/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filr_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:08:30 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/23 16:18:43 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdir.h"

static char		get_type(mode_t mode)
{
	if (S_ISLNK(mode))
		return ('l');
	else if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISSOCK(mode))
		return ('s');
	else
		return ('?');
}

char			ft_file_type(char *path)
{
	struct stat	buf;

	if (!path || !(*path))
		return (0);
	if (stat(path, &buf) == -1)
		return (0);
	return (get_type(buf.st_mode));
}
