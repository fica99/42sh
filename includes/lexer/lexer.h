/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 19:39:11 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/01 17:52:39 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# define LEXER_COLS 100
# define LEXER_ROWS 200

typedef struct s_lexer
{
	int rows;
	int cols;
	int **matrix;
}				t_lexer;

typedef struct	s_token
{
	char		*lexeme;
	token_type	type;
	token_class	class;
}				t_token;

char		*check_token_type(t_token *token, int type);
char		*check_token_class(t_token *token, int class);
void		free_token(t_token **token);
t_lexer *load_lexer(char *path);
t_lexer *new_lexer(void);
int     **create_lexer_matrix(int rows, int cols);
int     load_new_line(int **matrix_row, char *line, int *cols);
char    *get_start_position(char *line);
int     check_coll(char *position);

#endif
