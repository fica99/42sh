/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_table.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:06:10 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/19 13:12:10 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# include <dirent.h>
# include <stdlib.h>

# define PREV_CUR_DIR 2
# define FT_PATH_MAX 1000

/*
**	hash_table.c
*/
t_hash	**init_bin_table(size_t *bin_table_size);
size_t	get_bin_table_size(char **path);
t_hash	**make_bin_table(char **path, size_t size);
DIR		*check_open(char *path);
void	check_close(DIR *folder);
/*
**	free_bin_table.c
*/
t_hash	**free_bin_table(t_hash **bin_table, size_t *bin_table_size);
#endif
