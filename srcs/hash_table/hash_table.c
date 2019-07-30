/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:25:18 by aashara-          #+#    #+#             */
/*   Updated: 2019/07/30 00:48:22 by aashara-         ###   ########.fr       */
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
	ft_free_dar(path);
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
