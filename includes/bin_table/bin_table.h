/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_table.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:06:10 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/21 19:03:23 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# include <dirent.h>
# include <stdlib.h>

# define PREV_CUR_DIR 2
# define PATH_MAX 1000

typedef struct	s_bin_table
{
	size_t	bin_table_size;
	t_hash	**bin_table;
}				t_bin_table;

/*
**	hash_table.c
*/
void	init_bin_table(t_bin_table *bin_table);
size_t	get_bin_table_size(char **path);
t_hash	**make_bin_table(char **path, size_t size);
DIR		*check_open(char *path);
void	check_close(DIR *folder);
/*
**	free_bin_table.c
*/
void	free_bin_table(t_bin_table *bin_table);

t_bin_table	g_bin_table;
#endif
