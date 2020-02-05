/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_autocom_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:51:02 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/03 22:33:19 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static char		*rl_autocom_path_split(char *path, char **file)
{
	int		i;
	char	*pwd;
	char	*full_path;

	i = ft_strlen(path) - 1;
	if (!(pwd = get_var("PWD", ENV)))
		rl_err("42sh", "pwd error", NOERROR);
	if (!(full_path = ft_strnew(ft_strlen(pwd) + ft_strlen(path) + 1)))
		rl_err("42sh", "malloc() error", ENOMEM);
	while (i >= 0 && path[i] != '/')
		--i;
	if (path[0] != '/')
	{
		ft_strcat(ft_strcpy(full_path, pwd), "/");
		if (i > 0)
			full_path = ft_strncat(full_path, path, i);
	}
	else
		ft_strncpy(full_path, path, i + 1);
	if (!(*file = ft_strdup(path + i + 1)))
		rl_err("42sh", "malloc() error", ENOMEM);
	return (full_path);
}

static void		rl_autocom_check_files(char **files, char *file)
{
	short	len;
	short	i;
	short	j;

	i = -1;
	len = ft_strlen(file);
	while (files[++i])
	{
		if (ft_strncmp(files[i], file, len))
		{
			j = i;
			ft_strdel(&files[j]);
			while (files[j + 1])
			{
				files[j] = files[j + 1];
				++j;
			}
			files[j] = NULL;
			--i;
		}
	}
}

char			**rl_autocom_path(char *path)
{
	char	*file;
	char	**content;
	char	*full_path;

	file = NULL;
	content = NULL;
	full_path = rl_autocom_path_split(path, &file);
	if (!access(full_path, 4) && ft_file_type(full_path) == 'd')
	{
		if (!(content = ft_dir_content(full_path, 0)))
			rl_err("42sh", "malloc() error", ENOMEM);
		rl_autocom_check_files(content, file);
	}
	ft_strdel(&full_path);
	ft_strcpy(path, file);
	ft_strdel(&file);
	return (content);
}
