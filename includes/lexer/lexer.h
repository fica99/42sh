/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 21:19:01 by ggrimes           #+#    #+#             */
/*   Updated: 2019/08/31 14:07:33 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# define LEXER_COLS 100
# define LEXER_ROWS 200

typedef struct	s_matrix
{
	int	rows;
	int	cols;
	int	**data;
}				t_matrix;

typedef struct	s_lexer
{
	t_matrix	*m_type;
	t_matrix	*m_class;
}				t_lexer;

t_lexer		*load_lexer(void);
char		*get_load_matrix_path(void);
t_lexer		*new_lexer(void);
t_matrix	*get_matrix(char *path);
t_matrix	*load_matrix_from_file(int fd);
t_matrix	*new_matrix(void);
int			**create_lexer_matrix(int rows, int cols);
int			load_new_line(t_matrix *matrix, char *line);
char		*get_start_position(char *line);
int			check_coll(char *position);

//debug
void		print_matrix(t_matrix *matrix);

#endif
