/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:27:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/19 18:46:19 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_hash	*make_table(void)
{
    t_hash  		*table;
    char   		 	**path;
	DIR				*folder;
	struct dirent	*file;

	if (!(table = (t_hash*)malloc(sizeof(t_hash*) * g_term.hash_table_size)))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
    if (!(path = ft_strsplit(ft_getenv("PATH"), '/')))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	while (path)
	{
		folder = check_open(path);
		while ((file = readdir(folder)) != NULL)
		{
			table[hash_index(hashing(file->d_name))] = ;
		}
		check_close(folder);
		path++;
	}
	free_double_arr(path);
    return (table);
}
