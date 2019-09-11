/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:35:55 by filip             #+#    #+#             */
/*   Updated: 2019/09/11 16:37:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char		*get_folder(void)
{
	char	*path;

	path = NULL;
	if (ft_getenv("PWD") && ft_getenv("HOME"))
	{
		if (!(path = ft_strdup(ft_strrchr(ft_getenv("PWD"), '/') + 1)))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
		if (!ft_strcmp(ft_getenv("PWD"), ft_getenv("HOME")))
		{
			ft_strclr(path);
			ft_strcat(path, "~");
		}
	}
	return (path);
}

char		*get_path(void)
{
	char	*path;

	path = NULL;
	if (ft_getenv("PWD") && ft_getenv("HOME"))
	{
		if (!ft_strncmp(ft_getenv("PWD"), ft_getenv("HOME"),
		ft_strlen(ft_getenv("HOME"))))
		{
			if (!(path = ft_strjoin("~", ft_getenv("PWD")
			+ ft_strlen(ft_getenv("HOME")))))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
		}
		else
		{
			if (!(path = ft_strdup(ft_getenv("PWD"))))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
		}
	}
	return (path);
}
