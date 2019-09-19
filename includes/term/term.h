/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:03:47 by filip             #+#    #+#             */
/*   Updated: 2019/09/19 21:43:49 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_H
# define TERM_H

# include <unistd.h>

typedef struct		s_term
{
	char			*buffer;
	char			*copy_line;
	size_t			bin_table_size;
	t_hash			**bin_table;
	t_history		history;
}					t_term;

typedef struct		s_string
{
	char			*str;
	short			index;
}					t_string;

struct s_line		g_line;

/*
**	ft_term.c
*/
void				term_start(t_term *term);
void				init_term(void);
void				init_global_var(char **argv, char **environ);
void				check_valid_string(t_term *term);
#endif
