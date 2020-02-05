/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 00:05:38 by ggrimes           #+#    #+#             */
/*   Updated: 2019/09/15 21:23:12 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdir.h"

size_t	ft_size_dir(char *dirpath)
{
	size_t	size;
	DIR		*dirp;

	size = 0;
	if (!dirpath)
		return (size);
	if (!(dirp = opendir(dirpath)))
		return (0);
	while (readdir(dirp))
		size++;
	if (closedir(dirp) == -1)
		return (0);
	return (size);
}
