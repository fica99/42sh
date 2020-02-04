/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hash_tables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 18:01:44 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/04 19:15:45 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_hash_tables.h"

void			init_builtins_hash_table(void)
{
	g_builins_hash_table.size = BUILTINS_NB;
	g_builins_hash_table.table = init_hash_table(BUILTINS_NB);
	// push_hash(g_builins_hash_table.table, "pwd", &pwd, BUILT_NB);
	// push_hash(g_builins_hash_table.table, "cd", &cd, BUILT_NB);
	// push_hash(g_builins_hash_table.table, "echo", &ft_echo, BUILT_NB);
	// push_hash(g_builins_hash_table.table, "exit", &exit_built, BUILT_NB);
	// push_hash(g_builins_hash_table.table, "hash", &hash, BUILT_NB);
	// push_hash(g_builins_hash_table.table, "set", &set, BUILT_NB);
//	// push_hash(g_builins_hash_table.table, "set_var", &set_var, BUILT_NB);
	// push_hash(g_builins_hash_table.table, "fg", &fg, BUILT_NB);
	// push_hash(g_builins_hash_table.table, "bg", &bg, BUILT_NB);
	// push_hash(g_builins_hash_table.table, "jobs", &jobs, BUILT_NB);
	// push_hash(g_builins_hash_table.table, "fc", &fc, BUILT_NB);
	// push_hash(g_builins_hash_table.table, "type", &ft_type, BUILT_NB);
	// push_hash(g_builins_hash_table.table, "export", &export, BUILT_NB);
	// push_hash(table, "test", &ft_test, BUILT_NUM);
	// push_hash(g_builins_hash_table.table, "unset", &unset, BUILT_NB);
}

static size_t	get_bin_table_size(char **path)
{
	size_t	i;
	short	j;
	short	size;

	i = 0;
	j = -1;
	while (path[++j])
		if ((size = ft_size_dir(path[j])))
			i += (size - PREV_CUR_DIR_NB);
	return (i);
}

static t_hash	**make_bin_table(char **path, size_t size)
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
				if (!(full_path = ft_strnew(PATH_MAX)))
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

void	init_bin_hash_table(void)
{
	char	*var_path;
	char	**path;

	g_bin_hash_table.size = 0;
	g_bin_hash_table.table = NULL;
	if (!(var_path = get_var("PATH", ENV)))
		return ;
	if (!(path = ft_strsplit(var_path, ':')))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	if ((g_bin_hash_table.size = get_bin_table_size(path)))
		g_bin_hash_table.table = make_bin_table(path, g_bin_hash_table.size);
	ft_free_dar(path);
}
