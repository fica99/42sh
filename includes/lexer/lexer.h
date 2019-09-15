/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 21:19:01 by ggrimes           #+#    #+#             */
/*   Updated: 2019/09/15 23:58:51 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# define LEXER_COLS 100
# define LEXER_ROWS 200
# define LEXER_STR_LEN 256
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
	t_matrix	*m_union;
}				t_lexer;

enum    token_type
{
	FT_ERROR = -2,
	SEP = 1,
	EOL = 2,
	EXPRESS = 3,
	SPACE = 4,
	LRED = 5,
	DLRED = 6,
	RRED = 7,
	DRRED = 8,
	PIPE = 9,
	BRKO = 10,
	BRKC = 11,
	DBRKO = 12,
	DBRKC = 13,
	RBRKO = 14,
	RBRKC = 15,
	NUM = 16,
	ERRED = 20,
	EDRRED = 21,
	ARRED = 23,
	ADRRED = 24
};

typedef enum token_type		token_type;

enum    token_class
{
	C_OTHER = 0,
	C_FT_ERROR = 1,
	C_SEP = 2,
	C_EXPRESS = 3,
	C_LREDIR = 4,
	C_RREDIR = 5,
	C_BRK = 6,
	C_NUM = 7,
	C_CLOSE = 8
};

typedef enum	token_class	token_class;

typedef struct	s_token
{
	char		*lexeme;
	token_type	type;
	token_class	class;
	int			start_index;
	int			fin_index;
}				t_token;

/*
 * struct s_tokens
 * pc - state (previous -> current)
 * cn - state (current -> next)
 */

typedef struct	s_tokens
{
	t_token	*previous;
	t_token	*current;
	t_token	*next;
	int		pc;
	int		cn;
}				t_tokens;


typedef struct	s_lexer_params
{
	int		index;
	int		state;
	int		type;
	int		s_index;
	char	str[LEXER_STR_LEN];
}				t_lexer_params;


/* lexer.c */
t_token		*get_next_token(t_string *str, t_lexer *lexer);
int			init_tokens(t_tokens *tokens, t_string *str, t_lexer *lexer);
int			check_tokens(t_tokens *tokens, t_lexer *lexer, t_string *str);
int			check_union(t_token *token, t_token *next_token, t_lexer *lexer);
int			miss_token(t_tokens *tokens);
int			completed_token(t_tokens *tokens, t_string *str);
int			different_tokens(t_tokens *tokens, t_string *str);
int			equal_tokens(t_tokens *tokens, t_string *str);
t_token		*get_union_token(t_lexer *lexer);
char		*join_lexeme(char *dest, char *src);
void		clear_token(t_token **token);
t_token		*check_space(t_token *token, t_string *str, t_lexer *lexer);
int			init_next_token(t_token **token, t_string *str, t_lexer *lexer);
t_token		*check_next_token(t_token *token, t_string *str, t_lexer *lexer);
t_token		*no_union(t_token *token, t_token *next_token, t_string *str);
t_token		*join_token(t_token *token, t_token *next_token, t_lexer *lexer, int state);

/* delete */
int			check_stack(t_token **token, t_token **next_token);
int			check_union(t_token *token, t_token *next_token, t_lexer *lexer);
int			union_tokens(t_token **token, t_token **next_token, int t_union);
int			go_ahead(char *str, int cur_index, int cur_type, t_lexer *lexer);
int			generalize_type(int type, t_matrix *m_generalization);
/* load_lexer.c */
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
/* get_token.c */
t_token		*get_token(t_string *str, t_lexer *lexer);
void		initial_lexer_params(t_lexer_params *prm, int start_index);
int			next_state(char symbol, int state, t_lexer *lexer);
int			add_symbol(t_lexer_params *prm, char sym);
t_token		*new_token(void);
/* get_token2.c */
t_token		*ready_token(t_string *str, t_lexer_params prm);
int			define_class(int type, t_matrix *m_class);
/* error_token.c */
t_token		*token_error(void);
t_token		*class_error(t_token *token, t_token *next_token);
t_token		*eof_token(void);
int			tokens_error(t_tokens *tokens, t_string *str);
/* debug_token.c */
void		print_matrix(t_matrix *matrix);
void		print_token(t_string *str);

#endif
