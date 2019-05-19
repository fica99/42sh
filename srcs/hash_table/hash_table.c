/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:25:18 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/20 00:42:10 by filip            ###   ########.fr       */
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
	//free_double_arr(path);

}

size_t	get_hash_table_size(char **path)
{
	DIR				*folder;
	size_t			i;
	struct dirent	*file;

	i = 0;
	while (*path)
	{
		folder = check_open(*path);
		while ((file = readdir(folder)) != NULL)
			i++;
		check_close(folder);
		path++;
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

size_t	hash_index(size_t key)
{
	return (key % g_term.hash_table_size);
}