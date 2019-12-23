/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:25:18 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/06 13:36:19 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	init_bin_table(t_table *table)
{
	char	*env_path;
	char	**path;
	t_hash	**bin_table;
	size_t	bin_table_size;

	table->size = 0;
	table->table = NULL;
	if (!(env_path = get_env("PATH", ENV)))
		return ;
	if (!(path = ft_strsplit(env_path, ':')))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	if ((bin_table_size = get_bin_table_size(path)))
		bin_table = make_bin_table(path, bin_table_size);
	else
		bin_table = NULL;
	ft_free_dar(path);
	table->table = bin_table;
	table->size = bin_table_size;
}

size_t	get_bin_table_size(char **path)
{
	size_t	i;
	short	j;
	short	size;

	i = 0;
	j = -1;
	while (path[++j])
		if ((size = ft_size_dir(path[j])))
			i += (size - PREV_CUR_DIR);
	return (i);
}

t_hash	**make_bin_table(char **path, size_t size)
{
	t_hash			**table;
	DIR				*folder;
	struct dirent	*f;
	char			*full_path;

	if (!(table = init_hash_table(size)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	while (*path)
	{
		if ((folder = opendir(*path)))
		{
			while ((f = readdir(folder)))
			{
				if (!ft_strcmp(f->d_name, ".") || !ft_strcmp(f->d_name, ".."))
					continue ;
				if (!(full_path = ft_strnew(FT_PATH_MAX)))
					err_exit("42sh", "malloc() error", NULL, ENOMEM);
				table = push_hash(table, f->d_name, (void*)ft_strcat(ft_strcat(
					ft_strcat(full_path, *path), "/"), f->d_name), size);
			}
			closedir(folder);
		}
		++path;
	}
	return (table);
}

void	free_table(t_table *table)
{
	table->table = free_hash_table(table->table, table->size,
	FREE_TABLE_DATA);
	table->size = 0;
}
