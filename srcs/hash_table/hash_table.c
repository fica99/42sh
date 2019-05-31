/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:25:18 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/31 01:08:48 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			make_hash_table(void)
{
	char	*env_path;
	char	**path;

	if (!(env_path = ft_getenv("PATH")))
	{
		g_term.hash_table_size = 0;
		g_term.hash_table = NULL;
		return ;
	}
	if (!(path = ft_strsplit((ft_getenv("PATH")), ':')))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	g_term.hash_table_size = get_hash_table_size(path);
	g_term.hash_table = make_table(path);
	free_double_arr(path);
}

unsigned short	get_hash_table_size(char **path)
{
	DIR				*folder;
	unsigned short	i;
	short			j;
	struct dirent	*file;

	i = 0;
	j = -1;
	while (path[++j])
	{
		folder = check_open(path[j]);
		while ((file = readdir(folder)))
		{
			if (!ft_strcmp(file->d_name, ".") || !ft_strcmp(file->d_name, ".."))
				continue ;
			i++;
		}
		check_close(folder);
	}
	return (i);
}

DIR				*check_open(char *path)
{
	DIR	*folder;

	if (!(folder = opendir(path)))
		print_error("42sh", "opendir() error", path, 0);
	return (folder);
}

void			check_close(DIR *folder)
{
	if (closedir(folder) == -1)
		print_error("42sh", "opendir() error", NULL, 0);
}

unsigned short	hash_index(unsigned short key)
{
	return (key % g_term.hash_table_size);
}
