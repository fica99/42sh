/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:03:47 by filip             #+#    #+#             */
/*   Updated: 2019/06/25 20:31:19 by aashara-         ###   ########.fr       */
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
}					t_cord;

typedef struct		s_buff
{
	char			*buffer;
	short			malloc_len;
	char			*history_search;
	short			history_search_malloc_len;
	char			*save_buff;
	short			save_malloc_len;
	char			*copy_buff;
	short			copy_malloc_len;
	char			*prev_line;
	short			prev_line_len;
}					t_buff;

typedef struct		s_hash
{
	char			*path;
	unsigned short	index;
	char			*name;
	struct s_hash	*next;
}					t_hash;

typedef struct		s_history
{
	char			**history_buff;
	short			history_index;
	char			*history_path;
}					t_history;

typedef struct		s_term
{
	char			**env_cp;
	struct termios	savetty;
	unsigned short	hash_table_size;
	t_cord			*cord;
	t_hash			**hash_table;
	t_history		*history;
	t_buff			*buffer;
}					t_term;

void				term_start(t_term *term);
void				term_prompt(void);
void				init_term(void);
void				reset_term(void);
#endif
