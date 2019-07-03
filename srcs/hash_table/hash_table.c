/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:25:18 by aashara-          #+#    #+#             */
/*   Updated: 2019/07/03 17:12:17 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			init_hash_table(t_term *term)
{
	char	*env_path;
	char	**path;

	if (!(env_path = ft_getenv("PATH")))
	{
		term->hash_table_size = 0;
		term->hash_table = NULL;
		return ;
	}
	if (!(path = ft_strsplit((ft_getenv("PATH")), ':')))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	term->hash_table_size = get_hash_table_size(path);
	term->hash_table = make_hash_table(path, term->hash_table_size);
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

unsigned short	hash_index(unsigned short key, unsigned short len)
{
	return (key % len);
}
