/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 23:37:26 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/01 23:37:35 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdir.h"

char	*ft_read_file(char *path)
{
	int		fd;
	int		res;
	char	*content;
	char	*buff;
	char	*copy;

	if ((fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
		return (NULL);
	if (!(content = ft_strnew(1)))
		return (NULL);
	while ((res = get_next_line(fd, &buff)) > 0)
	{
		copy = content;
		if (!(content = ft_strjoin(copy, buff)))
			return (NULL);
		ft_strdel(&buff);
		ft_strdel(&copy);
	}
	if (res == -1)
		return (NULL);
	if ((close(fd)) == -1)
		return (NULL);
	return (content);
}
