/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:25:18 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/23 22:16:59 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	init_bin_table(t_bin_table *table)
{
	char	*env_path;
	char	**path;
	t_hash	**bin_table;
	size_t	bin_table_size;

	table->bin_table_size = 0;
	table->bin_table = NULL;
	if (!(env_path = ft_getenv("PATH")))
		return ;
	if (!(path = ft_strsplit(env_path, ':')))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	bin_table_size = get_bin_table_size(path);
	bin_table = make_bin_table(path, bin_table_size);
	ft_free_dar(path);
	table->bin_table = bin_table;
	table->bin_table_size = bin_table_size;
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

	if (!(table = init_hash_table(size)))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	j = -1;
	while (path[++j])
	{
		folder = check_open(path[j]);
		while ((file = readdir(folder)))
		{
			if (!ft_strcmp(file->d_name, ".") || !ft_strcmp(file->d_name, ".."))
				continue ;
			if (!(full_path = ft_strnew(FT_PATH_MAX)))
				err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
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
		err_exit(g_argv[0], "opendir() error", path, NOERROR);
	return (folder);
}

void	check_close(DIR *folder)
{
	if (closedir(folder) == -1)
		err_exit(g_argv[0], "opendir() error", NULL, NOERROR);
}
