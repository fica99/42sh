/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:03:47 by filip             #+#    #+#             */
/*   Updated: 2019/08/01 13:46:35 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_H
# define TERM_H

# include <unistd.h>

typedef struct		s_cord
{
	short			x_start;
	short			y_start;
	short			x_cur;
	short			y_cur;
	short			ws_col;
	short			ws_row;
	short			highlight_pos;
	short			pos;
	struct s_cord	*nl;
}					t_cord;

typedef struct		s_buff
{
	char			*buffer;
	short			malloc_len;
}					t_buff;

typedef struct		s_history
{
	char			**history_buff;
	short			history_index;
	char			*history_path;
}					t_history;

typedef struct		s_line
{
	t_buff			buffer;
	t_buff			history_search;
	t_buff			save_buff;
	t_buff			copy_buff;
	t_cord			*cord;
	t_history		history;
}					t_line;

typedef struct		s_hash
{
	char			*path;
	char			*name;
	struct s_hash	*next;
}					t_hash;

typedef struct		s_term
{
	char			*copy_line;
	unsigned short	hash_table_size;
	t_hash			**hash_table;
	t_history		history;
	char			*buffer;
}					t_term;

void				term_start(t_term *term);
void				init_term(void);
#endif
