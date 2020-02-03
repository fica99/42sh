/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hash_tables.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:59:17 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/03 22:16:16 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXEC_HASH_TABLES_H
# define EXEC_HASH_TABLES_H

# include <limits.h>
# include "libft.h"
# include "libhash.h"
# include "libdir.h"
# include "variables.h"
# include "error.h"

# define PREV_CUR_DIR_NB 2
# define BUILTINS_NB 15
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

t_table			g_bin_hash_table;
t_table			g_builins_hash_table;
#endif
