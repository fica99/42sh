/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 20:27:40 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/22 20:32:24 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char		*get_path(void)
{
	char	*path;
	char	*pwd;
	char	*home;

	path = NULL;
	if ((pwd = ft_getenv("PWD")) && (home = ft_getenv("HOME")))
	{
		if (!ft_strncmp(pwd, home, ft_strlen(home)))
		{
			if (!(path = ft_strjoin("~", pwd + ft_strlen(home))))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
		}
		else
		{
			if (!(path = ft_strdup(pwd)))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
		}
	}
	return (path);
}

char		*get_cur_dir(void)
{
	char	*path;
	char	*pwd;
	char	*home;
	char	*folder;

	path = NULL;
	if ((pwd = ft_getenv("PWD")) && (home = ft_getenv("HOME")))
	{
		if (*(folder = ft_strrchr(pwd, '/') + 1) == '\0')
			folder--;
		if (!(path = ft_strdup(folder)))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
		if (!ft_strcmp(pwd, home))
		{
			ft_strclr(path);
			ft_strcat(path, "~");
		}
	}
	return (path);
}
