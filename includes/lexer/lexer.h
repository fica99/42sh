/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 21:19:01 by ggrimes           #+#    #+#             */
/*   Updated: 2019/09/08 19:53:59 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# define LEXER_COLS 100
# define LEXER_ROWS 200
# define LEXER_STR_LEN 256
# define LEXER_SPACE 20
# define LEXER_MATRIX_PATH "srcs/lexer/"


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
	t_matrix	*m_generalization;
}				t_lexer;

enum    token_type
{
	FT_ERROR = -2,
	SEP = 1,
	EOL = 2,
	EXPRESS = 3,
	LRED = 4,
	DLRED = 5,
	RRED = 6,
	DRRED = 7,
	PIPE = 8,
	ARRED = 16,
	ERRED = 18,
	DERRED = 19,
	ADRRED = 21,
	RREDA = 22,
	DRREDA = 23
};

typedef enum token_type		token_type;

enum    token_class
{
	C_OTHER = 0,
	C_FT_ERROR = 1,
	C_SEP = 2,
	C_EXPRESS = 3,
	C_REDIR = 4,
	C_CLOSE = 5
};

typedef enum	token_class	token_class;

typedef struct	s_token
{
	char		*lexeme;
	token_type	type;
	token_class	class;
}				t_token;

typedef struct	s_lexer_params
{
	int		index;
	int		state;
	int		type;
	int		s_index;
	char	str[LEXER_STR_LEN];
}				t_lexer_params;

//load_matrix
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
void		clear_lexer(t_lexer **lexer);
void		clear_matrix(t_matrix **matrix);

//lexer
t_token		*get_next_token(t_string *str, t_lexer *lexer);
void		initial_lexer_params(t_lexer_params *prm, int start_index);
int			next_state(char symbol, int state, t_lexer *lexer);
int			go_ahead(char *str, int cur_index, int cur_type, t_lexer *lexer);
int			add_symbol(t_lexer_params *prm, char sym);
t_token		*new_token(void);
t_token		*ready_token(t_string *str, t_lexer_params prm, t_lexer *lexer);
int			generalize_type(int type, t_matrix *m_generalization);
int			define_class(int type, t_matrix *m_class);
t_token		*token_error(void);
t_token		*class_error(t_token **token);
t_token		*eof_token(void);

//debug
void		print_matrix(t_matrix *matrix);
void		print_token(t_string *str);

#endif
