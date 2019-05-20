/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:27:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/21 01:09:44 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_hash	**make_table(char **path)
{
    t_hash  		**table;
	DIR				*folder;
	struct dirent	*file;
	short			j;

	table = init_table();
	j = -1;
    while (path[++j])
	{
		folder = check_open(path[j]);
		while ((file = readdir(folder)) != NULL)
			table = write_hash(file->d_name, path[j], table);
		check_close(folder);
	}
    return (table);
}

t_hash	**init_table(void)
{
	t_hash			**table;
	unsigned short	i;

	if (!(table = (t_hash**)malloc(sizeof(t_hash*) * (g_term.hash_table_size + 1))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	i = -1;
	while (++i <= g_term.hash_table_size)
		table[i] = NULL;
	return (table);
}

t_hash	*init_hash(void)
{
	t_hash	*hash;

	if (!(hash = (t_hash*)malloc(sizeof(t_hash))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	hash->name = NULL;
	hash->path = NULL;
	hash->next = NULL;
	return (hash);
}

t_hash	**write_hash(char *str, char *path, t_hash **table)
{
	unsigned short	index;
	t_hash			*copy;
	char			*copy_path;
	t_hash			*next;

	index = hash_index(hashing(str));
	copy = init_hash();
	if (!(copy_path = ft_strnew(ft_strlen(path) + 1)))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	copy_path = ft_strcpy(copy_path, path);
	copy->name = ft_strdup(str);
	copy->path = ft_strjoin(ft_strcat(copy_path, "/"), str);
	copy->index = index;
	ft_memdel((void**)&copy_path);
	if (!(next = table[index]))
		table[index] = copy;
	else
	{
		while (next->next)
			next = next->next;
		next->next = copy;
	}
	return (table);
}

unsigned short	hashing(char *str)
{
	char			 ret_size;
	unsigned short	ret;
    char			per_char;

	ret_size = 16;
	ret = 0x5555;
	per_char = 7;
    while (*str)
	{
		ret ^= *str++;
		ret = ((ret << per_char) | (ret >> (ret_size - per_char)));
	}
	return ret;
}