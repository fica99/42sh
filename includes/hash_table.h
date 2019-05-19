/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:06:10 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/19 18:47:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# include <dirent.h>

typedef struct s_hash
{
	char			*path;
	char			*name;
	struct s_hash	*next;
}				t_hash;

void			make_hash_table(void);
unsigned short	get_hash_table_size(void);
unsigned short	hash_index(int key);
DIR				*check_open(char *path);
void			check_close(DIR *folder);
t_hash			*make_table(void);
void			free_hash_table(void);
#endif
