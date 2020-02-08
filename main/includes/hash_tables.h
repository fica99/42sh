/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tables.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:59:16 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/08 18:38:39 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLES_H
# define HASH_TABLES_H

# include <limits.h>
# include "libft.h"
# include "libhash.h"
# include "libdir.h"
# include "variables.h"
# include "error.h"
# define PREV_CUR_DIR_NB 2
# define BUILTINS_NB 16
# define ALIASES_HASH_TABLE_SIZE 1000

typedef struct	s_table
{
	size_t		size;
	t_hash		**table;
}				t_table;

/*
**				init_hash_tables.c
*/
void			init_builtins_hash_table(void);
void			init_bin_hash_table(void);
void			init_aliases_hash_table(void);

t_table			g_bin_hash_table;
t_table			g_builtins_hash_table;
t_table			g_aliases_hash_table;
#endif
