/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:25:18 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/19 13:12:19 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_hash	**init_bin_table(size_t *bin_table_size)
{
	char	*env_path;
	char	**path;
	t_hash	**bin_table;

	*bin_table_size = 0;
	if (!(env_path = ft_getenv("PATH")))
		return (NULL);
	if (!(path = ft_strsplit(env_path, ':')))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	*bin_table_size = get_bin_table_size(path);
	bin_table = make_bin_table(path, *bin_table_size);
	ft_free_dar(path);
	return (bin_table);
}

size_t	get_bin_table_size(char **path)
{
	size_t	i;
	short	j;
	short	size;

	i = 0;
	j = -1;
	while (path[++j])
	{
		if ((size = ft_size_dir(path[j])))
			i += (size - PREV_CUR_DIR);
	}
	return (i);
}

t_hash	**make_bin_table(char **path, size_t size)
{
	t_hash			**table;
	DIR				*folder;
	struct dirent	*file;
	short			j;
	char			*full_path;

	table = init_hash_table(size);
	j = -1;
	while (path[++j])
	{
		folder = check_open(path[j]);
		while ((file = readdir(folder)))
		{
			if (!ft_strcmp(file->d_name, ".") || !ft_strcmp(file->d_name, ".."))
				continue ;
			if (!(full_path = ft_strnew(FT_PATH_MAX)))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
			ft_strcat(ft_strcat(ft_strcat(full_path, path[j]), "/"), file->d_name);
			table = push_hash(table, file->d_name, full_path, size);
		}
		check_close(folder);
	}
	return (table);
}

DIR		*check_open(char *path)
{
	DIR	*folder;

	if (!(folder = opendir(path)))
		err_exit("42sh", "opendir() error", path, NOERROR);
	return (folder);
}

void	check_close(DIR *folder)
{
	if (closedir(folder) == -1)
		err_exit("42sh", "opendir() error", NULL, NOERROR);
}
