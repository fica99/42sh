/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 21:19:01 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/18 21:09:05 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
# define CALC_H

# include "libft.h"
# include "variables.h"

# define CALC_TOKENS_SIZE 100

typedef enum			e_calc_tkntype
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
	CALC_LPARENT = 19,
	CALC_RPARENT = 20,
	CALC_VAR = 21
}						t_calc_tkntype;

typedef struct			s_calc_tkn
{
	void				*value;
	t_calc_tkntype		type;
	size_t				start_pos;
	size_t				end_pos;
}						t_calc_tkn;

typedef	struct			s_calc_tkns
{
	t_calc_tkn			*tokens;
	size_t				size;
	size_t				malloc_size;
}						t_calc_tkns;

typedef enum			e_calc_err_type
{
	CALC_ERR_NULL_OR_IND = 1,
	CALC_ERR_LX = 2,
	CALC_ERR_SYNTAX = 3,
	CALC_ERR_DIV_ZERO = 4,
	CALC_ERR_PARENT = 5
}						t_calc_err_type;

typedef struct			s_calc_err
{
	t_calc_err_type		type;
	int					status;
}						t_calc_err;

typedef struct			s_calc_var
{
	char				*value;
	size_t				size;
}						t_calc_var;

/*
** calc_lexer.c
*/

t_calc_tkn				*calc_get_next_tkn(char *str, size_t pos);
t_calc_tkn				*calc_define_tkn(char *str, size_t pos);
t_calc_tkn				*calc_define_tkn_next(char *str, size_t pos);

/*
** calc_error_fun.c
*/

long long				calc_error(t_calc_err *error, t_calc_err_type type);

/*
** calc_tkn.c
*/

t_calc_tkn				*calc_newtkn(char *value, t_calc_tkntype type);
void					calc_del_tkn(t_calc_tkn **token);

/*
** calc_arr_tkns.c
*/

t_calc_tkns				*calc_get_arr_tkns(char *str, t_calc_tkns *s_tokens,
	size_t index);
t_calc_tkns				*calc_del_tkns(t_calc_tkns *s_tokens);
int						calc_check_index(t_calc_tkns *s_tokens, size_t index);

/*
** calc_arr_reloc.c
*/

t_calc_tkns				*calc_reloc_tkns(t_calc_tkns *s_tokens);

/*
** calc_num_fun.c
*/

t_calc_tkn				*calc_get_number_tkn(char *str, size_t pos);
long long				calc_number(t_calc_tkns *s_tokens, size_t *index,
	t_calc_err *error);
long long				calc_unary(t_calc_tkns *s_tokens, size_t *index,
	t_calc_err *error);

/*
** calc_add_fun.c
*/

t_calc_tkn				*calc_get_add_tkn(char *str, size_t pos);
long long				calc_add_sub(t_calc_tkns *s_tokens, size_t *index,
	t_calc_err *error);

/*
** calc_mul_fun.c
*/

t_calc_tkn				*calc_get_mul_mod_tkn(char *str, size_t pos);
long long				calc_mul_div_mod(t_calc_tkns *s_tokens, size_t *index,
	t_calc_err *error);

/*
** calc_inc_fun.c
*/

t_calc_tkn				*calc_get_inc_tkn(char *str, size_t pos);

/*
** calc_com_fun.c
*/

t_calc_tkn				*calc_get_com_tkn(char *str, size_t pos);
long long				calc_com(t_calc_tkns *s_tokens, size_t *index,
	t_calc_err *error);

/*
** calc_eq_fun.c
*/

t_calc_tkn				*calc_get_eq_tkn(char *str, size_t pos);
long long				calc_eq_diff(t_calc_tkns *s_tokens, size_t *index,
	t_calc_err *error);

/*
** calc_log_fun.c
*/

t_calc_tkn				*calc_get_log_tkn(char *str, size_t pos);
long long				calc_log(t_calc_tkns *s_tokens, size_t *index,
	t_calc_err *error);

/*
** calc.c
*/

long long				calc(char *str, t_calc_err *error);
long long				calc_exp(t_calc_tkns *s_tokens, size_t index,
	t_calc_err *error);

/*
** calc_parent_fun.c
*/

t_calc_tkn				*calc_get_parent_tkn(char *str, size_t pos);
long long				calc_parent(t_calc_tkns *s_tokens, size_t *index,
	t_calc_err *error);

/*
** calc_var_tkn.c
*/
int						calc_check_var(char *str, t_calc_var *var);
int						calc_var_is_valid(char *str);
t_calc_tkn				*calc_get_var_tkn(char *str, size_t pos,
													t_calc_var *var);

/*
** calc_var_fun.c
*/

long long				calc_var(t_calc_tkns *s_tokens, size_t *index,
	t_calc_err *error);
long long				calc_var_inc(t_calc_tkns *s_tokens, size_t *index,
	t_calc_err *error);
t_calc_tkns				*calc_prefix(char *str, t_calc_tkns *s_tokens,
															size_t*pos);

/*
** calc_atoi.c
*/

long long				calc_ll_atoi(const char *str);

/*
** calc_ltoa.c
*/

char					*calc_ltoa(long long num);

#endif
