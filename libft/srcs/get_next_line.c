/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 13:08:38 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/11 19:00:32 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_new_line(char **arr, int *end)
{
	int		i;
	char	*arr_new;
	char	*arr1;

	i = 0;
	if (**arr == '\0' || *arr == NULL)
	{
		*end = 0;
		return (NULL);
	}
	while (*(*arr + i) && *(*arr + i) != '\n')
		i++;
	if (*(*arr + i) == '\n')
	{
		*(*arr + i) = '\0';
		i++;
	}
	arr_new = ft_strdup(*arr);
	arr1 = ft_strdup(*arr + i);
	free(*arr);
	*arr = arr1;
	return (arr_new);
}

int			get_next_line(const int fd, char **line)
{
	int			end;
	int			nb;
	char		buf[BUFF_SIZE + 1];
	static char	*arr[1];
	char		*arr1;

	if (fd < 0 || line == NULL)
		return (-1);
	end = 1;
	while ((nb = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (!arr[fd])
			arr[fd] = ft_strnew(1);
		buf[nb] = '\0';
		arr1 = ft_strjoin(arr[fd], buf);
		free(arr[fd]);
		arr[fd] = arr1;
		arr1 = NULL;
		if (ft_strchr(arr[fd], '\n') != NULL)
			break ;
	}
	if (nb < 0 || (nb == 0 && arr[fd] == NULL))
		return (-1);
	*line = find_new_line(&arr[fd], &end);
	return (end);
}
