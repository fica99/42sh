/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:25:18 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/19 18:36:35 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

unsigned short	hash_index(int key)
{
	return (key % g_term.hash_table_size);
}

void			make_hash_table(void)
{
	if (!(g_term.hash_table_size = get_hash_table_size()))
	{
		g_term.hash_table = NULL;
		return ;
	}
	g_term.hash_table = make_table();

}

unsigned short	get_hash_table_size(void)
{
	char			**path;
	char			*env_path;
	DIR				*folder;
	unsigned short	i;
	struct dirent	*file;

	if (!(env_path = ft_getenv("PATH")))
			return (0);
	if (!(path = ft_strsplit(env_path, '/')))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	i = 0;
	while (path)
	{
		folder = check_open(path);
		while ((file = readdir(folder)) != NULL)
			i++;
		check_close(folder);
		path++;
	}
	free_double_arr(path);
	return (i);
}

DIR				*check_open(char *path)
{
	DIR	*folder;

	if (!(folder = opendir(path)))
		print_error("42sh", "opendir() error", path, NULL);
	return (folder);
}

void			check_close(DIR *folder)
{
	if (closedir(folder) == -1)
		print_error("42sh", "opendir() error", path, NULL);
}
