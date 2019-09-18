/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:03:47 by filip             #+#    #+#             */
/*   Updated: 2019/09/18 20:58:59 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_H
# define TERM_H

# include <unistd.h>

typedef struct		s_temp
{
	char			*template;
	void			(*handler)();
	struct s_temp	*next;
}					t_temp;

typedef struct		s_term
{
	char			*buffer;
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
/*
**	templates.c
*/
t_temp				*init_templates(void);
t_temp				*init_temp_struct(char *template, void (*handler)());
void				free_templates(t_temp **head);
/*
**	set_templates.c
*/
t_temp				*set_templates(void);
t_temp				*set_esc_templates(void);
t_temp				*set_other_templates(char *str);
/*
**	free_line.c
*/
void				free_line(t_line *line);
void				free_cord(t_cord **cord);
void				free_buffer(t_buff *buffer);
/*
**	init_line.c
*/
void				init_line(t_line *line, t_term *term);
void				init_buff(t_buff *buffer);
t_cord				*init_cord(void);
#endif
