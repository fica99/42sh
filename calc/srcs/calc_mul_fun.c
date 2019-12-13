/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_mul_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 20:11:13 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/07 17:30:16 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

static t_calc_tkntype	calc_mul_type(char *str)
{
	if (!str)
		return (0);
	if (*str == '*')
		return (CALC_MUL);
	else if (*str == '/')
		return (CALC_DIV);
	else if (*str == '%')
		return (CALC_MOD);
	else
		return (0);
}

static int				calc_div_mod(int result, t_calc_tkns *s_tokens,
	size_t *index, t_calc_err *error)
{
	int				next_result;
	t_calc_tkntype	type;

	type = s_tokens->tokens[*index].type;
	(*index)++;
	next_result = calc_com(s_tokens, index, error);
	if (error->status)
		return (0);
	if (!next_result)
		return (calc_error(error, CALC_ERR_DIV_ZERO));
	if (type == CALC_DIV)
		return (result / next_result);
	else if (type == CALC_MOD)
		return (result % next_result);
	else
		return (calc_error(error, CALC_ERR_SYNTAX));
}

static int				calc_mul_div_mod_next(int result, t_calc_tkns *s_tokens,
	size_t *index, t_calc_err *error)
{
	t_calc_tkntype	type;

	while (1)
	{
		type = s_tokens->tokens[*index].type;
		if (type == CALC_MUL)
			(*index)++;
		if (type == CALC_MUL)
			result *= calc_com(s_tokens, index, error);
		else if (type == CALC_DIV || type == CALC_MOD)
			result = calc_div_mod(result, s_tokens, index, error);
		else
			break ;
		if (error->status)
			return (0);
	}
	return (result);
}

t_calc_tkn				*calc_get_mul_mod_tkn(char *str, size_t pos)
{
	t_calc_tkn		*token;
	t_calc_tkntype	type;

	if (!str)
		return (NULL);
	type = calc_mul_type(str);
	if (!(token = calc_newtkn(NULL, type)))
		return (NULL);
	token->start_pos = pos;
	token->end_pos = pos + 1;
	return (token);
}

int						calc_mul_div_mod(t_calc_tkns *s_tokens,
	size_t *index, t_calc_err *error)
{
	int		result;

	if (!s_tokens || !calc_check_index(s_tokens, *index))
		return (calc_error(error, CALC_ERR_NULL_OR_IND));
	result = calc_com(s_tokens, index, error);
	if (error->status)
		return (0);
	result = calc_mul_div_mod_next(result, s_tokens, index, error);
	return (result);
}
