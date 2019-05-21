/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:06:10 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/21 12:34:07 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# include <dirent.h>

typedef struct s_hash
{
	char			*path;
	unsigned short	index;
	char			*name;
	struct s_hash	*next;
}				t_hash;

void			make_hash_table(void);
unsigned short	get_hash_table_size(char **path);
unsigned short	hash_index(unsigned short key);
DIR				*check_open(char *path);
void			check_close(DIR *folder);
t_hash			**make_table(char **path);
t_hash			**init_table(void);
t_hash			*init_hash(void);
unsigned short	hashing(char *str);
void			write_hash(char *str, char *path, t_hash **table);
void			free_hash_table(void);
#endif
