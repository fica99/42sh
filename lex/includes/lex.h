/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 21:19:01 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/08 22:06:02 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <fcntl.h>
# include <time.h>
# include "libft.h"
# include "libhash.h"
# include "libstr.h"
# include "libdar.h"

# define LEX_TOKENS_SIZE 100

typedef enum	e_lex_tkn_type
{
	T_NULL,
	T_ERR,
	T_END,					// "\0"
	T_WORD,					// "ls ."
	T_PIPE,					// "|"
	T_GREATER,				// ">"
	T_GREATER_GREATER,		// ">>"
	T_LESS,					// "<"
	T_LESS_LESS,			// "<<"
	T_LESS_AND,				// "<&"
	T_GREATER_AND,			// ">&1"
	T_SEP					// ";"
}				t_lex_tkn_type;

typedef enum	e_lex_tkn_class
{
	C_NULL,
	C_END,
	C_WORD,
	C_PIPE,
	C_REDIR,				// "T_GREATER, T_GREATER_GREATER, T_LESS, T_LESS_LESS, T_LESS_AND, T_GREATER_AND"
	C_SEP
}				t_lex_tkn_class;

typedef struct	s_lex_tkn
{
	char			*value;
	t_lex_tkn_type	type;
	t_lex_tkn_class	class;
	size_t			start_pos;
	size_t			end_pos;

}				t_lex_tkn;

typedef	struct	s_lex_tkns
{
	t_lex_tkn	**tokens;
	size_t		malloc_size;
	size_t		size;
}				t_lex_tkns;

/*
** lex_lexer.c
*/

t_lex_tkn		**lex_get_tkns(char **str);
t_lex_tkn		*lex_get_next_tkn(char	**str, size_t pos);

/*
** lex_tkn.c
*/

t_lex_tkn		*lex_new_tkn(void);
t_lex_tkn		*lex_del_tkn(t_lex_tkn *token);

/*
** lex_tkns.c
*/

t_lex_tkns		*lex_new_tkns(void);
t_lex_tkns		*lex_tkns_reloc(t_lex_tkns *s_tokens);
t_lex_tkn		**lex_del_tkns(t_lex_tkn **tokens);
t_lex_tkn		**lex_del_s_tokens(t_lex_tkns *s_tokens);

/*
** lex_get_tkn.c
*/

t_lex_tkn		*lex_get_next_tkn(char	**str, size_t pos);
void			lex_fill_value_pos(t_lex_tkn *token, char *str,
	size_t start_pos, size_t pos);

/*
** lex_check_tkn.c
*/

t_lex_tkn_type	lex_check_end(char **str, short is_word, size_t *pos);
t_lex_tkn_type	lex_check_alnum(char **str, short is_word, size_t *pos);
t_lex_tkn_type	lex_check_other(char **str, short is_word, size_t *pos);

/*
** lex_tkn_type.c
*/

t_lex_tkn_type	lex_check_type(char **str, short is_word, size_t *pos);

/*
** lex_tkn_class.c
*/

t_lex_tkn_class	lex_check_class(t_lex_tkn_type type);

/*
** lex_check_or.c
*/

t_lex_tkn_type	lex_check_or(char **str, short is_word, size_t *pos);

/*
** lex_check_greater.c
*/

t_lex_tkn_type	lex_check_greater(char **str, short is_word, size_t *pos);
int				lex_check_fd_redir(char *str, short is_word, size_t *pos);

/*
** lex_check_less.c
*/

t_lex_tkn_type	lex_check_less(char **str, short is_word, size_t *pos);

/*
** lex_check_sep.c
*/

t_lex_tkn_type	lex_check_sep(char **str, short is_word, size_t *pos);

/*
** lex_check_quotes.c
*/

int				lex_is_quote(char c);
int				lex_check_quotes(char *str, size_t *pos);

/*
** lex_debug.c
*/

void			lex_print_tkns(t_lex_tkn **tokens);
void			lex_print_tkn(t_lex_tkn *token);
void			lex_print_type(t_lex_tkn_type type);
void			lex_print_class(t_lex_tkn_class class);

#endif
