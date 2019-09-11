/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:25:18 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/11 16:38:57 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_hash	**init_hash_table(unsigned short *hash_table_size)
{
	char	*env_path;
	char	**path;
	t_hash	**hash_table;

	*hash_table_size = 0;
	if (!(env_path = ft_getenv("PATH")))
		return (NULL);
	if (!(path = ft_strsplit((ft_getenv("PATH")), ':')))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	*hash_table_size = get_hash_table_size(path);
	hash_table = make_hash_table(path, *hash_table_size);
	ft_free_dar(path);
	return (hash_table);
}

unsigned short	get_hash_table_size(char **path)
{
	unsigned short	i;
	short			j;
	short			size;

	i = 0;
	j = -1;
	while (path[++j])
	{
		if ((size = ft_size_dir(path[j])))
			i += (size - PREV_CUR_DIR);
	}
	return (i);
}

DIR				*check_open(char *path)
{
	DIR	*folder;

	if (!(folder = opendir(path)))
		err_exit("42sh", "opendir() error", path, NOERROR);
	return (folder);
}

void			check_close(DIR *folder)
{
	if (closedir(folder) == -1)
		err_exit("42sh", "opendir() error", NULL, NOERROR);
}

unsigned short	hash_index(unsigned short key, unsigned short len)
{
	return (key % len);
}
