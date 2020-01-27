/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:06:10 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/26 17:52:14 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# define PREV_CUR_DIR 2
# define PREV_D ".."
# define CUR_D "."
# define FT_PATH_MAX 1000
# define BUILT_NUM 16
# define FREE_TABLE_DATA 1

# include "error.h"
# include "libft.h"
# include "libdir.h"
# include "libdar.h"
# include "libhash.h"

typedef struct	s_table
{
	size_t		size;
	t_hash		**table;
}				t_table;

/*
**	hash_table.c
*/
void			init_bin_table(t_table *bin_table);
size_t			get_bin_table_size(char **path);
t_hash			**make_bin_table(char **path, size_t size);
void			free_table(t_table *table);

void			init_built_table(t_table *g_built_table);

t_table			g_built_table;
t_table			g_bin_table;
#endif
