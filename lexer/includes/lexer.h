/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 21:19:01 by ggrimes           #+#    #+#             */
/*   Updated: 2019/10/19 19:21:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# define LEXER_COLS 100
# define LEXER_ROWS 200
# define LEXER_STR_LEN 256
# define LEXER_MATRIX_PATH "lexer/matrix"
# define LEXER_SKIP_CLASS C_SKIP
# define LEXER_ADD_SPACE_CLASS C_EXPRESS

typedef struct		s_string
{
	char			*str;
	short			index;
}					t_string;

typedef struct		s_matrix
{
	int				rows;
	int				cols;
	int				**data;
}					t_matrix;

typedef struct		s_lexer
{
	t_matrix		*m_type;
	t_matrix		*m_class;
	t_matrix		*m_union;
	t_matrix		*m_priority;
	t_matrix		*m_generalization;
}					t_lexer;

typedef enum		e_token_type
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
	ADRRED = 25,
	CLOSE_FD = 28
}					t_token_type;

typedef enum		e_token_class
{
	C_OTHER = 0,
	C_SKIP = 1,
	C_FT_ERROR = 2,
	C_SEP = 3,
	C_EXPRESS = 4,
	C_LREDIR = 5,
	C_RREDIR = 6,
	C_BRK = 7,
	C_NUM = 8,
	C_CLOSE = 9
}					t_token_class;

typedef struct		s_token
{
	char			*lexeme;
	t_token_type	type;
	t_token_class	class;
	int				start_index;
	int				fin_index;
}					t_token;

typedef struct		s_tokens
{
	t_token			*previous;
	t_token			*current;
	t_token			*next;
	int				union_pc;
	int				union_cn;
	int				priority_pc;
	int				priority_cn;
	char			*error_msg;
}					t_tokens;

typedef struct		s_lexer_params
{
	int				index;
	int				state;
	int				type;
	int				s_index;
	char			str[LEXER_STR_LEN];
}					t_lexer_params;

/*
**	lexer.c
*/
t_token				*get_next_token(t_string *str, t_lexer *lexer);
int					lx_get_union_params(t_tokens *tokens, t_lexer *lexer);
int					lx_get_priority_params(t_tokens *tokens, t_lexer *lexer);
void				lx_clear_token(t_token **token);
int					lx_no_previous(t_tokens *tokens, t_string *str,
t_lexer *lexer);
/*
**	check_tokens.c
*/
int					lx_check_tokens(t_tokens *tokens,
t_lexer *lexer, t_string *str);
int					lx_miss_token(t_tokens *tokens, t_string *str);
int					lx_completed_token(t_tokens *tokens, t_string *str);
int					lx_equal_tokens(t_tokens *tokens, t_string *str);
/*
**	init_tokens.c
*/
int					lx_init_tokens(t_tokens *tokens, t_string *str,
t_lexer *lexer);
int					lx_init_next_token(t_tokens *tokens,
t_string *str, t_lexer *lexer);
t_token				*lx_skip(t_token *token, t_string *str, t_lexer *lexer);
/*
**	union_token.c
*/
t_token				*lx_get_union_token(t_lexer *lexer, t_string *str);
t_token				*lx_join_token(t_token *token, t_token *next_token);
int					lx_generalization_type(int	type,
t_matrix *m_generalization);
char				*lx_del_spaces(char *lexeme);
/*
**	different_tokens.c
*/
int					lx_different_tokens(t_tokens *tokens, t_string *str);
int					lx_left_priority(t_tokens *tokens, t_string *str);
int					lx_right_priority(t_tokens *tokens, t_string *str);
/*
**	check_matrixs.c
*/
int					lx_define_union(t_token *token,
t_token *next_token, t_lexer *lexer);
int					lx_define_priority(t_token *token,
t_token *next_token, t_lexer *lexer);
int					lx_define_state(char symbol, int state, t_lexer *lexer);
/*
**	load_lexer.c
*/
t_lexer				*load_lexer(void);
char				*get_load_matrix_path(void);
t_lexer				*new_lexer(void);
t_matrix			*get_matrix(char *path);
int					check_coll(char *position);
/*
**	load_matrix.c
*/
t_matrix			*new_matrix(void);
int					**create_lexer_matrix(int rows, int cols);
t_matrix			*load_matrix_from_file(int fd);
int					load_new_line(t_matrix *matrix, char *line);
char				*get_start_position(char *line);
/*
**	clear_lexer.c
*/
void				clear_lexer(t_lexer **lexer);
void				clear_matrix(t_matrix **matrix);
/*
**	get_token.c
*/
t_token				*lx_get_token(t_string *str, t_lexer *lexer);
void				initial_lexer_params(t_lexer_params *prm, int start_index);
int					add_symbol(t_lexer_params *prm, char sym);
t_token				*new_token(void);
/*
**	get_token2.c
*/
t_token				*lx_ready_token(t_string *str,
t_lexer_params prm, t_lexer *lexer);
int					lx_define_class(int type, t_matrix *m_class);
/*
**	error_token.c
*/
t_token				*lx_token_error(char *msg, t_string *str);
t_token				*lx_class_error(t_token *token,
t_token *next_token, char *msg, t_string *str);
t_token				*lx_eof_token(void);
int					lx_tokens_error(t_tokens *tokens, t_string *str);
int					lx_put_error(t_tokens *tokens, char *msg);

t_lexer				*g_lexer;
#endif
