/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 21:19:01 by ggrimes           #+#    #+#             */
/*   Updated: 2019/11/21 20:20:54 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
# define CALC_H
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

typedef enum		e_calc_tkntype
{
	CALC_ERROR = 1,
	CALC_END = 2,
	CALC_NUMBER = 3,
	CALC_PLUS = 4,
	CALC_MINUS = 5,
	CALC_MUL = 6,
	CALC_DIV = 7,
	CALC_MOD = 8,
	CALC_INC = 9,
	CALC_DEC = 10,
	CALC_LESS = 11,
	CALC_MORE = 12,
	CALC_LESSOREQ = 13,
	CALC_MOREOREQ = 14,
	CALC_EQ = 15,
	CALC_DIFF = 16,
	CALC_AND = 17,
	CALC_OR = 18,
	CALC_PREFIXVAR = 19,
	CALC_VAR = 20
}					t_calc_tkntype;

typedef struct	s_calc_tkn
{
	void				*value;
	t_calc_tkntype		type;
	size_t				start_pos;
	size_t				end_pos;
	struct s_calc_tkn	*left;
	struct s_calc_tkn	*right;
}				t_calc_tkn;

typedef enum		e_var_type
{
	VAR_STR = 1,
	VAR_INT = 2
}					t_var_type;

typedef struct		s_variable
{
	char		*name;
	t_var_type	type;
	void		*value;
}					t_variable;

typedef struct		s_variables
{
	t_variable	*data;
	size_t		size;
}					t_variables;


/*
** calc_lexer.c 
 */

t_calc_tkn				*calc_get_next_tkn(char *str, size_t pos, t_variables *variables);
t_calc_tkn				*calc_newtkn(void *value, t_calc_tkntype type);
t_calc_tkn  			*calc_define_tkn(char *str, size_t pos, t_variables *variables);
t_calc_tkn  			*calc_get_number_tkn(char *str, size_t pos);
void    				calc_del_tkn(t_calc_tkn **token);
t_calc_tkn  			*calc_define_tkn_next(char *str, size_t pos, t_variables *variables);

/*
** calc_add_fun.c
 */

t_calc_tkn  			*calc_get_add_tkn(char *str, size_t pos);

/*
** calc_mul_fun.c
 */

t_calc_tkn  			*calc_get_mul_tkn(char *str, size_t pos);

/*
** calc_mul_fun.c
 */

t_calc_tkn  			*calc_get_inc_tkn(char *str, size_t pos);

/*
** calc_com_fun.c
 */

t_calc_tkn  			*calc_get_com_tkn(char *str, size_t pos);

/*
** calc_eq_fun.c
 */

t_calc_tkn  			*calc_get_eq_tkn(char *str, size_t pos);

/*
** calc_log_fun.c
 */

t_calc_tkn  			*calc_get_log_tkn(char *str, size_t pos);

/*
** calc_var_fun.c
 */

t_calc_tkn  			*calc_get_var_tkn(char *str, size_t pos, int var_id, t_variables *variables);
int         			calc_check_variables(char *str, t_variables *variables);

/*
** calc.c 
 */

int						calc(char *str, t_variables *variables);

/*
** calc_debug.c 
 */

void					calc_print_tkn(t_calc_tkn *token, t_variables *variables);
void    				calc_print_type(t_calc_tkntype type);
t_variables 			*calc_get_variables(void);

#endif