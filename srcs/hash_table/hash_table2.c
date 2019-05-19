/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:27:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/20 00:42:57 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_hash	*make_table(char **path)
{
    t_hash  		*table;
	DIR				*folder;
	struct dirent	*file;

	table = init_table();
    while (*path)
	{
		folder = check_open(*path);
		while ((file = readdir(folder)) != NULL)
			write_hash(file->d_name, *path, table);
		check_close(folder);
		path++;
	}
    return (table);
}

t_hash	*init_table(void)
{
	t_hash	*table;
	size_t	i;

	if (!(table = (t_hash*)malloc(sizeof(t_hash) * g_term.hash_table_size)))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	i = -1;
	while (++i < g_term.hash_table_size)
	{
		table[i].name = NULL;
		table[i].path = NULL;
		table[i].next = NULL;
	}
	return (table);
}

t_hash	*write_hash(char *str, char *path, t_hash *table)
{
	size_t	index;
	t_hash	copy;

	index = hash_index(hashing(str));
	copy = table[index];
	if (copy.name)
		copy = *(copy.next);
	copy.name = ft_strdup(str);
	copy.path = ft_strjoin(ft_strcat(path, "/"), str);
	copy.index = index;
	copy.next = NULL;
	return (table);
}

size_t	hashing(char *str)
{
	int ret_size;
    size_t ret;
    int per_char;

	ret_size = 32;
	ret = 0x555555;
	per_char = 7;
    while (*str)
	{
		ret ^= *str++;
		ret = ((ret << per_char) | (ret >> (ret_size - per_char)));
	}
	return ret;
}

void	free_hash_table(void)
{
	int		i;
	t_hash	*table;
	t_hash	*next;

	i = -1;
	table = g_term.hash_table;
	while (++i < g_term.hash_table_size)
	{
		if (table[i].name)
		{
			ft_memdel((void**)&table[i].name);
			ft_memdel((void**)&table[i].path);
			while ((next = table[i].next))
			{
				ft_memdel((void**)&next->name);
				ft_memdel((void**)&next->path);
			}
		}
	}
	ft_memdel((void**)&g_term.hash_table);
	g_term.hash_table_size = 0;
}